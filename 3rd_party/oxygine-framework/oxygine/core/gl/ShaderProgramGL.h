#pragma once
#include <QOpenGLShader>
#include "../ShaderProgram.h"

namespace oxygine
{
    class VertexDeclarationGL;
    class ShaderProgramGL : public ShaderProgram
    {
    public:
        ShaderProgramGL(QString vsShader, QString fsShader, const VertexDeclarationGL* decl);
        ~ShaderProgramGL();
        quint32    getID() const override;
        qint32             getUniformLocation(const char* id) const;
        virtual void bind() override;
    protected:
        void compileShader(QOpenGLShader& shader, QString data);
    private:
        GLuint _p;
        QOpenGLShaderProgram _program;
        QOpenGLShader _vsShader;
        QOpenGLShader _fsShader;
    };


}
