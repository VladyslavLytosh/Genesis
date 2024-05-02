#pragma once

#include "Genesis/Renderer/Shader.h"

namespace Genesis
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& filePath);
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        virtual void setBool(const std::string& name, bool value) const override;

        virtual void setIntUnf(const std::string& name, int value) const override;
        virtual void setIntUnf(const std::string& name, glm::ivec2 value) const override;
        virtual void setIntUnf(const std::string& name, glm::ivec3 value) const override;
        virtual void setIntUnf(const std::string& name, glm::ivec4 value) const override;

        virtual void setFloatUnf(const std::string& name, float value) const override;
        virtual void setFloatUnf(const std::string& name, glm::vec2 value) const override;
        virtual void setFloatUnf(const std::string& name, glm::vec3 value) const override;
        virtual void setFloatUnf(const std::string& name, glm::vec4 value) const override;

    private:
        struct ShaderProgramSource
        {
            std::string vertexSource;
            std::string fragmentSource;

            bool IsValid() const { return !vertexSource.empty() && !fragmentSource.empty(); }
        };

        ShaderProgramSource ParseShader();
        unsigned int CompileShader(const std::string& shaderSource, int shaderType);
        void CreateAndLinkShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

        std::string m_filePath;
        uint32_t m_RendererID;
    };
}  // namespace Genesis