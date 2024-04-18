#include "gspch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Genesis
{
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

		GS_CORE_INFO("OpenGL Info:");
		GS_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		GS_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		GS_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}