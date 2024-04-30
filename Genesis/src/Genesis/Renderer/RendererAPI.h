﻿#pragma once

#include "VertexArray.h"

#include <glm/vec4.hpp>

namespace Genesis
{
    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL = 1
        };

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<Genesis::VertexArray>& vertexArray) = 0;

        static API GetAPI() { return s_API; }

    private:
        static API s_API;
    };
}  // namespace Genesis