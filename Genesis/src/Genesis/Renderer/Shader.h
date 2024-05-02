#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Genesis
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void setBool(const std::string& name, bool value) const = 0;

        virtual void setIntUnf(const std::string& name, int value) const = 0;
        virtual void setIntUnf(const std::string& name, glm::ivec2 value) const = 0;
        virtual void setIntUnf(const std::string& name, glm::ivec3 value) const = 0;
        virtual void setIntUnf(const std::string& name, glm::ivec4 value) const = 0;

        virtual void setFloatUnf(const std::string& name, float value) const = 0;
        virtual void setFloatUnf(const std::string& name, glm::vec2 value) const = 0;
        virtual void setFloatUnf(const std::string& name, glm::vec3 value) const = 0;
        virtual void setFloatUnf(const std::string& name, glm::vec4 value) const = 0;

        static Shader* Create(const std::string& filePath);
        static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}  // namespace Genesis