#include "gspch.h"

#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Genesis
{
    OpenGLShader::OpenGLShader(const std::string& filePath) : m_filePath(std::move(filePath))
    {
        const ShaderProgramSource shaderSource = ParseShader();
        if (!shaderSource.IsValid())
        {
            return;
        }
        const unsigned int vertexShader = CompileShader(shaderSource.vertexSource, GL_VERTEX_SHADER);
        const unsigned int fragmentShader = CompileShader(shaderSource.fragmentSource, GL_FRAGMENT_SHADER);

        CreateAndLinkShaderProgram(vertexShader, fragmentShader);
    }

    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        const unsigned int vertexShader = CompileShader(vertexSrc, GL_VERTEX_SHADER);
        const unsigned int fragmentShader = CompileShader(fragmentSrc, GL_FRAGMENT_SHADER);

        CreateAndLinkShaderProgram(vertexShader, fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(0);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::UnBind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
    }

    void OpenGLShader::setIntUnf(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
    }

    void OpenGLShader::setIntUnf(const std::string& name, glm::ivec2 value) const
    {
        glUniform2i(glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y);
    }

    void OpenGLShader::setIntUnf(const std::string& name, glm::ivec3 value) const
    {
        glUniform3i(glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y, value.z);
    }

    void OpenGLShader::setIntUnf(const std::string& name, glm::ivec4 value) const
    {
        glUniform4i(glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::setFloatUnf(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
    }

    void OpenGLShader::setFloatUnf(const std::string& name, glm::vec2 value) const
    {
        glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y);
    }

    void OpenGLShader::setFloatUnf(const std::string& name, glm::vec3 value) const
    {
        glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y, value.z);
    }

    void OpenGLShader::setFloatUnf(const std::string& name, glm::vec4 value) const
    {
        glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y, value.z, value.w);
    }

    OpenGLShader::ShaderProgramSource OpenGLShader::ParseShader()
    {
        std::ifstream stream(m_filePath);

        if (!stream.good())
        {
            GS_CORE_CRITICAL("Can't open file {0}", m_filePath);
            return {"", ""};
        }

        enum class ShaderType
        {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;

        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos)
                {
                    type = ShaderType::FRAGMENT;
                }
            }
            else
            {
                ss[(int)type] << line << '\n';
            }
        }

        return {ss[0].str(), ss[1].str()};
    }
    unsigned int OpenGLShader::CompileShader(const std::string& shaderSource, int shaderType)
    {
        const unsigned int shader = glCreateShader(shaderType);
        const char* source = shaderSource.c_str();
        glShaderSource(shader, 1, &source, nullptr);

        // Compile the vertex shader
        glCompileShader(shader);

        int success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE)
        {
            int messageSize = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &messageSize);

            // The messageSize includes the NULL character
            std::vector<char> errorMessage(messageSize);
            glGetShaderInfoLog(shader, messageSize, nullptr, errorMessage.data());

            // We don't need the shader anymore.
            glDeleteShader(shader);

            GS_CORE_ERROR("{0}", errorMessage.data());
            GS_CORE_ASSERT(false, "Vertex shader compilation failure!")
        }
        return shader;
    }

    void OpenGLShader::CreateAndLinkShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
    {
        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_RendererID = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);

        glLinkProgram(m_RendererID);

        int success = 0;
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
}  // namespace Genesis