#pragma once

#include "Genesis/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace Genesis
{
    // TODO: Add OpenGL error handling
    class OpenGLContext : public RenderingContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };
}  // namespace Genesis