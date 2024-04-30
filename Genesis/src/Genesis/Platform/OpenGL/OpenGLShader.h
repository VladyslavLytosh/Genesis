#pragma once

#include "Genesis/Renderer/Shader.h"

namespace Genesis
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void UnBind() const override;

    private:
        uint32_t m_RendererID;
    };
}  // namespace Genesis