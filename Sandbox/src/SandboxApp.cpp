#include <Genesis.h>

#include "imgui/imgui.h"

#include "Genesis/Renderer/Renderer.h"
#include "Genesis/Renderer/Buffer.h"
#include "Genesis/Renderer/Shader.h"
#include "Genesis/Renderer/VertexArray.h"

class RenderLayer : public Genesis::Layer
{
public:
    virtual void OnAttach() override
    {
        m_VertexArray.reset(Genesis::VertexArray::Create());
        // clang-format off
        float vertices[] = 
        {
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        // clang-format on

        std::shared_ptr<Genesis::VertexBuffer> vertexBuffer(Genesis::VertexBuffer::Create(vertices, sizeof(vertices)));
        const Genesis::BufferLayout layout = {
            {Genesis::ShaderDataType::Float3, "a_Position"},
            {Genesis::ShaderDataType::Float3, "a_Color"},
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        // clang-format off
        uint32_t indices[] = 
        {
            0, 1, 2
        };
        // clang-format on

        std::shared_ptr<Genesis::IndexBuffer> indexBuffer(Genesis::IndexBuffer::Create(indices, 3));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        // clang-format off
        std::string vertexSrc = R"(
			    #version 460 core
			    
			    layout(location = 0) in vec3 a_Position;
			    layout (location = 1) in vec3 a_Color;

			    out vec3 ourColor;
			    void main()
			    {
				    gl_Position = vec4(a_Position, 1.0);	
				    ourColor = a_Color;
			    }
		    )";

        std::string fragmentSrc = R"(
			    #version 460 core
			    
			    out vec4 color;
			    in vec3 ourColor;
			    
			    void main()
			    {
				    color = vec4(ourColor, 1);
			    }
		    )";
        // clang-format on
        m_Shader.reset(Genesis::Shader::Create(vertexSrc, fragmentSrc));
    }

    virtual void OnUpdate() override
    {
        Genesis::RenderCommand::SetClearColor({0.8, 0.5, 0.2, 1});
        Genesis::RenderCommand::Clear();

        Genesis::Renderer::BeginScene();
        {

            m_Shader->Bind();
            Genesis::Renderer::Submit(m_VertexArray);
        }
        Genesis::Renderer::EndScene();
    }

private:
    std::shared_ptr<Genesis::Shader> m_Shader;
    std::shared_ptr<Genesis::VertexArray> m_VertexArray;
};

class Sandbox : public Genesis::Application
{
public:
    Sandbox() { PushLayer(new RenderLayer()); }

    virtual ~Sandbox() override = default;
};

Genesis::Application* Genesis::CreateApplication()
{
    return new Sandbox();
}