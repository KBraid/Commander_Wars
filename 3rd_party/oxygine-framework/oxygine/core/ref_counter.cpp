#include "3rd_party/oxygine-framework/oxygine/core/ref_counter.h"

#include <QObject>
#include <QThread>

namespace oxygine
{
    std::atomic<qint32> ref_counter::m_instanceCounter = 0;
#ifdef MEMORYTRACING
    QMutex ref_counter::m_lock;
    std::vector<ref_counter*> ref_counter::m_objects;
#endif
    void ref_counter::releaseRef()
    {
        if (--m_ref_counter <= 0)
        {
#ifdef MEMORYTRACING
            if (0 > m_ref_counter)
            {
                Q_ASSERT(false);
            }
#endif
            freeObject();
            QObject* pObj = dynamic_cast<QObject*>(this);
            if (pObj == nullptr)
            {
                delete this;
            }
            else
            {
                pObj->deleteLater();
            }
        }
    }

    void ref_counter::freeObject()
    {
        --m_instanceCounter;
#ifdef MEMORYTRACING
        m_lock.lock();
        auto cIter = m_objects.cbegin();
        while (cIter != m_objects.cend())
        {
            if (*cIter == this)
            {
                m_objects.erase(cIter);
            }
            else
            {
                ++cIter;
            }
        }
        m_lock.unlock();
#endif
    }

    void ref_counter::trackObject(ref_counter *pObj)
    {
        if (pObj->getRefCounter() == 0)
        {
            ++m_instanceCounter;
#ifdef MEMORYTRACING
            m_lock.lock();
            m_objects.push_back(pObj);
            m_lock.unlock();
#endif
        }
    }
}
