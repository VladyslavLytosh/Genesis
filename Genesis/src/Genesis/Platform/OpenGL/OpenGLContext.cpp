#include "gspch.h"

#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Genesis
{
    static void openGLDebugMessagesCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length,
                                            const char* message, const void* userParam)
    {
        // ignore non-significant error/warning codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        {
            return;
        }

        GS_CORE_ERROR("Debug message ({0}): {1}", id, message);
        switch (source)
        {
        case GL_DEBUG_SOURCE_API:
            GS_CORE_ERROR("Source: API");
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            GS_CORE_ERROR("Source: Window System");
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            GS_CORE_ERROR("Source: Shader Compiler");
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            GS_CORE_ERROR("Source: Third Party");
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            GS_CORE_ERROR("Source: Application");
            break;
        case GL_DEBUG_SOURCE_OTHER:
            GS_CORE_ERROR("Source: Other");
            break;
        }

        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            GS_CORE_ERROR("Type: Error");
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            GS_CORE_ERROR("Type: Deprecated Behaviour");
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            GS_CORE_ERROR("Type: Undefined Behaviour");
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            GS_CORE_ERROR("Type: Portability");
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            GS_CORE_ERROR("Type: Performance");
            break;
        case GL_DEBUG_TYPE_MARKER:
            GS_CORE_ERROR("Type: Marker");
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            GS_CORE_ERROR("Type: Push Group");
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            GS_CORE_ERROR("Type: Pop Group");
            break;
        case GL_DEBUG_TYPE_OTHER:
            GS_CORE_ERROR("Type: Other");
            break;
        }
        GS_CORE_ASSERT(false, "OpenGL debug message occured!")
    }

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    {
        GS_ASSERT(windowHandle, "Window handle is NULL")

        m_WindowHandle = windowHandle;
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        GS_CORE_ASSERT(status, "Failed to initialize Glad!")

        // Enabling openGL error callback system
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(openGLDebugMessagesCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

        GS_CORE_INFO("OpenGL Info:");
        GS_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        GS_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        GS_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}  // namespace Genesis