#include "gspch.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Genesis
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:
            return GL_FLOAT;
        case ShaderDataType::Float2:
            return GL_FLOAT;
        case ShaderDataType::Float3:
            return GL_FLOAT;
        case ShaderDataType::Float4:
            return GL_FLOAT;
        case ShaderDataType::Mat3:
            return GL_FLOAT;
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        case ShaderDataType::Int:
            return GL_INT;
        case ShaderDataType::Int2:
            return GL_INT;
        case ShaderDataType::Int3:
            return GL_INT;
        case ShaderDataType::Int4:
            return GL_INT;
        case ShaderDataType::Bool:
            return GL_BOOL;
        }

        GS_CORE_ASSERT(false, "Unknown ShaderDataType!")
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        (glCreateVertexArrays(1, &m_RendererID));
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        (glDeleteVertexArrays(1, &m_RendererID));
    }

    void OpenGLVertexArray::Bind() const
    {
        (glBindVertexArray(m_RendererID));
    }

    void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        GS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!")

        const auto& layout = vertexBuffer->GetLayout();
        uint32_t index = 0;
        for (const auto& element : layout)
        {
            glEnableVertexArrayAttrib(m_RendererID, index);
            glVertexArrayAttribBinding(m_RendererID, index, 0);
            glVertexArrayAttribFormat(m_RendererID, index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
                                      element.Normalized, element.Offset);
            ++index;
        }
        glVertexArrayVertexBuffer(m_RendererID, 0, vertexBuffer->GetID(), 0, (int)layout.GetStride());
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glVertexArrayElementBuffer(m_RendererID, indexBuffer->GetID());
        m_IndexBuffer = indexBuffer;
    }
}  // namespace Genesis