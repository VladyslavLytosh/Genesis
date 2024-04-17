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
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}