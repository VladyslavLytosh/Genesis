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
             -0.5f, -0.5f, 0.0f,
              0.5f,  0.5f, 0.0f,
              0.5f, -0.5f, 0.0f,
             -0.5f,  0.5f, 0.0f
        };

        // star vertices
        //float vertices[] = 
        //{
        //     0.0f,  0.75f, 0.0f, //  v2  0
        //    -0.15f, 0.25f, 0.0f, //  v1  1
        //    -0.5f,  0.25f, 0.0f, //  v0  2
        //    -0.25f, -0.15f, 0.0f, // v9  3
        //    -0.35f, -0.75f, 0.0f, // v8  4
        //    0.0f, -0.5f, 0.0f,  //   v7  5
        //    0.35f, -0.75f, 0.0f, //  v6  6
        //    0.25f, -0.15f, 0.0f, //  v5  7
        //    0.5f,  0.25f, 0.0f, //   v4  8
        //    0.15f, 0.25f, 0.0f, //   v3  9
        //};
        // clang-format on

        std::shared_ptr<Genesis::VertexBuffer> vertexBuffer(Genesis::VertexBuffer::Create(vertices, sizeof(vertices)));
        const Genesis::BufferLayout layout = {
            {Genesis::ShaderDataType::Float3, "a_Position"},
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        // clang-format off
        uint32_t indices[] = 
        {
            // star indices
            //0, 1, 9,
            //2, 3, 1,
            //4, 5, 3,
            //6, 5, 7,
            //8, 9, 7,
            //9, 3, 7,
            //1, 3, 9,
            //5, 7, 3

            0, 1, 3, // upper left triangle
            0, 2, 1 // lower right triangle
        };
        // clang-format on

        std::shared_ptr<Genesis::IndexBuffer> indexBuffer(Genesis::IndexBuffer::Create(indices, 6));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_Shader.reset(Genesis::Shader::Create("../Genesis/res/shaders/Basic.glsl"));
    }

    virtual void OnUpdate() override
    {
        Genesis::RenderCommand::SetClearColor(m_backgroundColor);
        Genesis::RenderCommand::Clear();

        Genesis::Renderer::BeginScene();
        {
            m_Shader->Bind();
            m_Shader->setFloatUnf("u_Color", m_rectangleColor);

            Genesis::Renderer::Submit(m_VertexArray);
        }
        Genesis::Renderer::EndScene();
    }
    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Scene properties");
        ImGui::ColorEdit4("Rectangle color", &m_rectangleColor[0]);
        ImGui::ColorEdit4("Clear color", &m_backgroundColor[0]);
        ImGui::End();
    }

private:
    glm::vec4 m_rectangleColor{0.3f, 0.8f, 0.5f, 1.f};
    glm::vec4 m_backgroundColor{0.8, 0.5, 0.2, 1};

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