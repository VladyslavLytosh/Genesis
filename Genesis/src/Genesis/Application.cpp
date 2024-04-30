#include "gspch.h"

#include "Application.h"

#include "Renderer/Renderer.h"

namespace Genesis
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        GS_CORE_ASSERT(!s_Instance, "Application alread exists!")
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(GS_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        m_VertexArray.reset(VertexArray::Create());
        // clang-format off
        float vertices[] = 
        {
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        // clang-format on

        std::shared_ptr<VertexBuffer> vertexBuffer(VertexBuffer::Create(vertices, sizeof(vertices)));
        const BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Color"},
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        // clang-format off
        uint32_t indices[] = 
        {
            0, 1, 2
        };
        // clang-format on

        std::shared_ptr<IndexBuffer> indexBuffer(IndexBuffer::Create(indices, 3));
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
        m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
    }

    Application::~Application()
    {
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(GS_BIND_EVENT_FN(Application::OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(event);
            // If we mark the event as
            // handled, there is no need to
            // propagate it down to the
            // layers.
            if (event.m_Handled)
            {
                break;
            }
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }

    void Application::Run()
    {
        while (m_Running)
        {
            RenderCommand::SetClearColor({0.8, 0.5, 0.2, 1});
            RenderCommand::Clear();

            Renderer::BeginScene();
            {

                m_Shader->Bind();
                Renderer::Submit(m_VertexArray);
            }
            Renderer::EndScene();

            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }
}  // namespace Genesis
