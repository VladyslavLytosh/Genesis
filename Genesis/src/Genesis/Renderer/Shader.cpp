#include "gspch.h"

#include "Shader.h"

#include <glad/glad.h>

namespace Genesis
{
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// Create an empty vertex shader handle
		const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const char* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, nullptr);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		int success = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			int messageSize = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &messageSize);

			// The messageSize includes the NULL character
			std::vector<char> errorMessage(messageSize);
			glGetShaderInfoLog(vertexShader, messageSize, nullptr, errorMessage.data());

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			GS_CORE_ERROR("{0}", errorMessage.data());
			GS_CORE_ASSERT(false, "Vertex shader compilation failure!")
			return;
		}

		const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, nullptr);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			int messageSize = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &messageSize);

			std::vector<char> errorMessage(messageSize);
			glGetShaderInfoLog(fragmentShader, messageSize, nullptr, errorMessage.data());

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			GS_CORE_ERROR("{0}", errorMessage.data());
			GS_CORE_ASSERT(false, "Fragment shader compilation failure!")
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			int messageSize = 0;
			glGetProgramiv(fragmentShader, GL_INFO_LOG_LENGTH, &messageSize);

			std::vector<char> errorMessage(messageSize);
			glGetProgramInfoLog(fragmentShader, messageSize, nullptr, errorMessage.data());

			glDeleteProgram(m_RendererID);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			GS_CORE_ERROR("{0}", errorMessage.data());
			GS_CORE_ASSERT(false, "Fragment shader compilation failure!")
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(0);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
}