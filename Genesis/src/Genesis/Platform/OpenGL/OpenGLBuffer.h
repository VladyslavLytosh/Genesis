#pragma once

#include "Genesis/Renderer/Buffer.h"

namespace Genesis
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual const BufferLayout& GetLayout() const override { return m_Layout; }
        virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

        virtual uint32_t GetID() const override { return m_RendererID; }

    private:
        uint32_t m_RendererID;

        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        virtual uint32_t GetCount() const override { return m_Count; }
        virtual uint32_t GetID() const override { return m_RendererID; }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}  // namespace Genesis