#include "3rd_party/oxygine-framework/oxygine/PostProcess.h"
#include "3rd_party/oxygine-framework/oxygine/RenderState.h"
#include "3rd_party/oxygine-framework/oxygine/STDRenderDelegate.h"
#include "3rd_party/oxygine-framework/oxygine/actor/Actor.h"
#include "3rd_party/oxygine-framework/oxygine/core/gl/ShaderProgramGL.h"
#include "3rd_party/oxygine-framework/oxygine/core/gl/VertexDeclarationGL.h"
#include "3rd_party/oxygine-framework/oxygine/core/oxygine.h"
#include "3rd_party/oxygine-framework/oxygine/core/Renderer.h"
#include "3rd_party/oxygine-framework/oxygine/core/gamewindow.h"
#include "3rd_party/oxygine-framework/oxygine/Clock.h"
#include "3rd_party/oxygine-framework/oxygine/res/Resource.h"

#include <qfile.h>
#include <qtextstream.h>


namespace oxygine
{
    spShaderProgram PostProcess::shaderBlurV ;
    spShaderProgram PostProcess::shaderBlurH;
    spShaderProgram PostProcess::shaderBlit;
    bool _ppBuilt = false;

    void PostProcess::initShaders()
    {
        if (_ppBuilt)
        {
            return;
        }
        _ppBuilt = true;

        spIVideoDriver driver = IVideoDriver::instance;

        const VertexDeclarationGL* decl = static_cast<const VertexDeclarationGL*>(IVideoDriver::instance->getVertexDeclaration(vertexPCT2::FORMAT));
        // read shader data
        QString vs_h;
        QString vs_v;
        QString fs_blur;
        QString vs_blit;
        QString fs_blit;
        QString filepath = "system/pp_hblur_vs.glsl";
        if (!QFile::exists(filepath))
        {
            filepath = oxygine::Resource::RCC_PREFIX_PATH + filepath;
        }
        if (QFile::exists(filepath))
        {
            QFile file(filepath);
            file.open(QIODevice::ReadOnly);
            QTextStream stream(&file);
            vs_h = stream.readAll();
        }
        filepath = "system/pp_vblur_vs.glsl";
        if (!QFile::exists(filepath))
        {
            filepath = oxygine::Resource::RCC_PREFIX_PATH + filepath;
        }
        if (QFile::exists(filepath))
        {
            QFile file(filepath);
            file.open(QIODevice::ReadOnly);
            QTextStream stream(&file);
            vs_v = stream.readAll();
        }
        filepath = "system/pp_rast_fs.glsl";
        if (!QFile::exists(filepath))
        {
            filepath = oxygine::Resource::RCC_PREFIX_PATH + filepath;
        }
        if (QFile::exists(filepath))
        {
            QFile file(filepath);
            file.open(QIODevice::ReadOnly);
            QTextStream stream(&file);
            fs_blur = stream.readAll();
        }
        filepath = "system/pp_blit_vs.glsl";
        if (!QFile::exists(filepath))
        {
            filepath = oxygine::Resource::RCC_PREFIX_PATH + filepath;
        }
        if (QFile::exists(filepath))
        {
            QFile file(filepath);
            file.open(QIODevice::ReadOnly);
            QTextStream stream(&file);
            vs_blit = stream.readAll();
        }
        filepath = "system/pp_blit_fs.glsl";
        if (!QFile::exists(filepath))
        {
            filepath = oxygine::Resource::RCC_PREFIX_PATH + filepath;
        }
        if (QFile::exists(filepath))
        {
            QFile file(filepath);
            file.open(QIODevice::ReadOnly);
            QTextStream stream(&file);
            fs_blit = stream.readAll();
        }
        // create shaders
        shaderBlurV = spShaderProgramGL::create(vs_v, fs_blur, decl);
        driver->setShaderProgram(shaderBlurV.get());
        driver->setUniformInt("s_texture", 0);
        shaderBlurH = spShaderProgramGL::create(vs_h, fs_blur, decl);
        driver->setShaderProgram(shaderBlurH.get());
        driver->setUniformInt("s_texture", 0);
        shaderBlit = spShaderProgramGL::create(vs_blit, fs_blit, decl);
        driver->setShaderProgram(shaderBlit.get());
        driver->setUniformInt("s_texture", 0);
    }

    void PostProcess::freeShaders()
    {
        shaderBlit = nullptr;
        shaderBlurH = nullptr;
        shaderBlurV = nullptr;
    }

    const qint32 ALIGN_SIZE = 256;
    const timeMS TEXTURE_LIVE = timeMS(3000);
    const qint32 MAX_FREE_TEXTURES = 3;

    using namespace std;

    DECLARE_SMART(TweenPostProcess, spTweenPostProcess);

    class PPTask;
    vector<PPTask*> postProcessItems;

    qint32 alignTextureSize(qint32 v)
    {
        qint32 n = (v - 1) / ALIGN_SIZE;
        return (n + 1) * ALIGN_SIZE;
    }

    class NTP
    {
    public:
        qint32 _w;
        qint32 _h;
        ImageData::TextureFormat _tf;
        NTP(qint32 w, qint32 h, ImageData::TextureFormat tf) : _w(w), _h(h), _tf(tf) {}

        bool operator()(const spNativeTexture& t1, const spNativeTexture&) const
        {
            if (t1->getFormat() < _tf)
            {
                return true;
            }
            if (t1->getWidth() < _w)
            {
                return true;
            }
            return t1->getHeight() < _h;
        }

        static bool cmp(const spNativeTexture& t2, const spNativeTexture& t1)
        {
            if (t1->getFormat() > t2->getFormat())
            {
                return true;
            }
            if (t1->getWidth() > t2->getWidth())
            {
                return true;
            }
            return t1->getHeight() > t2->getHeight();
        }
    };

    bool RenderTargetsManager::isGood(const spNativeTexture& t, qint32 w, qint32 h, ImageData::TextureFormat tf) const
    {
        if (!t)
        {
            return false;
        }
        if (!t->getHandle())
        {
            return false;
        }
        if (t->getFormat() == tf &&
            t->getWidth() >= w && t->getHeight() >= h &&
            t->getWidth() <= (w + ALIGN_SIZE) && t->getHeight() <= (h + ALIGN_SIZE))
        {
            return true;
        }
        return false;
    }

    spNativeTexture RenderTargetsManager::get(spNativeTexture current, qint32 w, qint32 h, ImageData::TextureFormat tf)
    {
        w = alignTextureSize(w);
        h = alignTextureSize(h);
        if (isGood(current, w, h, tf))
        {
            current->setCreationTime(Clock::getTimeMS());
            return current;
        }


        spNativeTexture result;

        auto it = lower_bound(m_free.cbegin(), m_free.cend(), result, NTP(w, h, tf));
        if (it != m_free.end())
        {
            const spNativeTexture& t = *it;
            if (isGood(t, w, h, tf))
            {
                result = t;
                m_free.erase(it);
            }
        }

        if (!result)
        {
            oxygine::handleErrorPolicy(oxygine::ep_show_error, "unable to find a render target");
        }
        result->setCreationTime(Clock::getTimeMS());
        m_rts.push_back(result);
        return result;
    }



    void RenderTargetsManager::update()
    {
        timeMS tm = Clock::getTimeMS();
        for (size_t i = 0, sz = m_rts.size(); i < sz; ++i)
        {
            spNativeTexture& texture = m_rts[i];
            if (texture->getRefCounter() == 1)
            {
                auto it = lower_bound(m_free.cbegin(), m_free.cend(), texture, NTP::cmp);
                m_free.insert(it, texture);
                m_rts.erase(m_rts.cbegin() + i);
                --i;
                --sz;
                continue;
            }
        }

        for (size_t i = 0, sz = m_free.size(); i < sz; ++i)
        {
            spNativeTexture& t = m_free[i];
            timeMS createTime = t->getCreationTime();
            if (createTime + TEXTURE_LIVE > tm)
            {
                continue;
            }
            m_free.erase(m_free.cbegin() + i);
            --i;
            --sz;
        }

        if (m_free.size() > MAX_FREE_TEXTURES)
        {
            m_free.erase(m_free.cbegin(), m_free.cbegin() + m_free.size() - MAX_FREE_TEXTURES);
        }
    }

    void RenderTargetsManager::reset()
    {
        for (qint32 i = 0; i < m_rts.size(); ++i)
        {
            m_rts[i]->release();
        }

        m_free.clear();
        m_rts.clear();
    }

    RenderTargetsManager _rtm;
    RenderTargetsManager& getRTManager()
    {
        return _rtm;
    }


    void addPostProcessItem(PPTask* task)
    {
        if (find(postProcessItems.begin(), postProcessItems.end(), task) == postProcessItems.end())
        {
            task->addRefPP();
            postProcessItems.push_back(task);
        }
    }


    void removePostProcessItem(PPTask* t)
    {
        vector<PPTask*>::iterator i = std::find(postProcessItems.begin(), postProcessItems.end(), t);
        if (i == postProcessItems.end())
        {
            return;
        }
        t->releaseRefPP();
        postProcessItems.erase(i);
    }


    bool _renderingPP = false;
    bool isRenderingPostProcessItems()
    {
        return _renderingPP;
    }

    void updatePortProcessItems()
    {
        if (!postProcessItems.empty())
        {
            _renderingPP = true;
            spIVideoDriver driver = IVideoDriver::instance;
            spNativeTexture prevRT = driver->getRenderTarget();
            ShaderProgram* sp = driver->getShaderProgram();

            for (size_t i = 0; i < postProcessItems.size(); ++i)
            {
                PPTask* p = postProcessItems[i];
                p->renderPP();
                p->releaseRefPP();
            }

            postProcessItems.clear();
            driver->setRenderTarget(prevRT);
            if (sp)
            {
                driver->setShaderProgram(sp);
            }
            _renderingPP = false;
        }

        _rtm.update();
    }

    void clearPostProcessItems()
    {
        postProcessItems.clear();
        _rtm.reset();
    }


    void pass(spNativeTexture srcTexture, const Rect& srcRect, spNativeTexture destTexture, const Rect& destRect, const QColor& color)
    {
        spIVideoDriver driver = IVideoDriver::instance;

        const VertexDeclarationGL* decl = static_cast<const VertexDeclarationGL*>(driver->getVertexDeclaration(vertexPCT2::FORMAT));
        driver->setRenderTarget(destTexture);
        driver->clear(QColor(0, 0, 0, 0));

        driver->setViewport(destRect);

        driver->setTexture(0, srcTexture);


        vertexPCT2 v[4];


        RectF dst = srcRect.cast<RectF>() / Vector2((float)srcTexture->getWidth(), (float)srcTexture->getHeight());
        fillQuadT(v,
                  dst,
                  RectF(-1, -1, 2, 2),
                  AffineTransform::getIdentity(), qRgba(color));


        driver->draw(IVideoDriver::PT_TRIANGLE_STRIP, decl, v, sizeof(v));
        driver->setTexture(0, spNativeTexture());
    }

    PostProcess::PostProcess(const PostProcessOptions& opt)
        : _extend(2, 2),
          _format(ImageData::TF_R8G8B8A8),
          _options(opt)

    {
    }

    void PostProcess::free()
    {
        _rt = 0;
    }

    Rect PostProcess::getScreenRect(const Actor& actor) const
    {
        if (_options._flags & PostProcessOptions::flag_screen)
        {
            return _screen;
        }
        GameWindow* window = oxygine::GameWindow::getWindow();
        QSize size = window->size();

        Rect display(Point(0, 0), Point(size.width(), size.height()));

        if (_options._flags & PostProcessOptions::flag_fullscreen)
        {
            return display;
        }
        RectF bounds = RectF::invalidated();
        AffineTransform transform = actor.computeGlobalTransform();
        if (_options._flags & PostProcessOptions::flag_fixedBounds)
        {
            const RectF& fb = _options._fixedBounds;
            bounds.unite(transform.transform(fb.getLeftTop()));
            bounds.unite(transform.transform(fb.getRightTop()));
            bounds.unite(transform.transform(fb.getRightBottom()));
            bounds.unite(transform.transform(fb.getLeftBottom()));
        }
        else
        {
            bounds = actor.computeBounds(transform);
        }
        Rect screen;
        screen = bounds.cast<Rect>();

        screen.size += Point(1, 1);
        screen.expand(_extend, _extend);

        if (!(_options._flags & PostProcessOptions::flag_singleR2T))
        {
            screen.clip(display);
        }
        return screen.cast<Rect>();
    }

    void PostProcess::update(Actor* actor)
    {
        _screen = getScreenRect(*actor);
        if (_screen.isEmpty())
        {
            return;
        }
        _rt = getRTManager().get(_rt, _screen.getWidth(), _screen.getHeight(), _format);


        _transform = actor->computeGlobalTransform().inverted();


        Material::null->apply();


        spIVideoDriver driver = IVideoDriver::instance;

        driver->setRenderTarget(_rt);

        Rect vp = _screen;
        vp.pos = Point(0, 0);
        driver->setViewport(vp);

        driver->clear(_options._clearColor);


        RenderState rs;
        spSTDRenderer renderer = STDRenderer::instance;


        RectF clip = vp.cast<RectF>();
        rs.clip = &clip;

        renderer->initCoordinateSystem(vp.getWidth(), vp.getHeight(), true);

        rs.transform = actor->getParent()->computeGlobalTransform();


        if (!(_options._flags & PostProcessOptions::flag_fullscreen))
        {
            AffineTransform offset;
            offset.identity();
            offset.translate(-_screen.pos);
            rs.transform = rs.transform * offset;
        }
        RenderDelegate* rd = actor->getRenderDelegate();
        actor->setRenderDelegate(STDRenderDelegate::instance.get());
        STDRenderDelegate::instance->RenderDelegate::render(actor, rs);

        STDRenderer::current->flush();

        actor->setRenderDelegate(rd);

        Material::null->apply();
    }

    TweenPostProcess::TweenPostProcess(const PostProcessOptions& opt)
        : m_actor(0),
          m_pp(opt),
          m_prevMaterial(0)
    {
    }

    TweenPostProcess::~TweenPostProcess()
    {
        removePostProcessItem(this);
        if (m_actor && m_actor->getRenderDelegate())
        {
            m_actor->setRenderDelegate(m_prevMaterial);
        }
    }


    void TweenPostProcess::renderPP()
    {
        if (m_pp._options._flags & PostProcessOptions::flag_singleR2T && m_pp._rt)
        {
            return;
        }
        m_pp.update(m_actor);
        _renderPP();
    }

    void TweenPostProcess::addRefPP()
    {
        m_pActorRef = m_actor;
    }

    void TweenPostProcess::releaseRefPP()
    {
        m_pActorRef = nullptr;
    }

    void TweenPostProcess::init(Actor& actor)
    {
        m_actor = &actor;
        m_prevMaterial = m_actor->getRenderDelegate();
        m_actor->setRenderDelegate(this);
    }

    void TweenPostProcess::update(Actor&, float p, const UpdateState&)
    {
        m_progress = p;
        addPostProcessItem(this);
    }

    void TweenPostProcess::done(Actor&)
    {
        if (m_actor->getRenderDelegate())
        {
            m_actor->setRenderDelegate(m_prevMaterial);
        }
    }

}
