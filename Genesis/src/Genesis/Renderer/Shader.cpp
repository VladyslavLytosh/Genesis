#include "gspch.h"

#include "Genesis/Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"
#include "Shader.h"

namespace Genesis
{
    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:
            GS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
            return nullptr;
        case RendererAPI::OpenGL:
            return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        GS_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}  // namespace Genesis