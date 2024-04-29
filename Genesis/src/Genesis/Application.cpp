#include "gspch.h"

#include "Application.h"
#include <glad/glad.h>

namespace Genesis {
Application *Application::s_Instance = nullptr;

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  switch (type) {
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

Application::Application() {
  GS_CORE_ASSERT(!s_Instance, "Application alread exists!")
  s_Instance = this;

  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallback(GS_BIND_EVENT_FN(Application::OnEvent));

  m_ImGuiLayer = new ImGuiLayer();
  PushOverlay(m_ImGuiLayer);

  float vertices[] = {0.0f, 0.5f, 0.0f, 1.0f,  0.0f,  0.0f, 0.5f, -0.5f, 0.0f,
                      0.0f, 1.0f, 0.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  1.0f};

  glGenVertexArrays(1, &m_VertexArray);
  glBindVertexArray(m_VertexArray);

  m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
  m_VertexBuffer->Bind();

  {
    const BufferLayout layout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float3, "a_Color"},
    };

    m_VertexBuffer->SetLayout(layout);
  }

  const auto &layout = m_VertexBuffer->GetLayout();

  uint32_t index = 0;
  for (const auto &element : layout) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, element.GetComponentCount(),
                          ShaderDataTypeToOpenGLBaseType(element.Type),
                          element.Normalized, (int)layout.GetStride(),
                          (const void *)element.Offset);
    ++index;
  }

  uint32_t indices[]{0, 1, 2};
  m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
  m_IndexBuffer->Bind();

  std::string vertexSrc = R"(
			#version 330 core
			
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
			#version 330 core
			
			out vec4 color;
			in vec3 ourColor;
			
			void main()
			{
				color = vec4(ourColor, 1);
			}
		)";

  m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
}

Application::~Application() {}

void Application::PushLayer(Layer *layer) { m_LayerStack.PushLayer(layer); }

void Application::PushOverlay(Layer *overlay) {
  m_LayerStack.PushOverlay(overlay);
}

void Application::OnEvent(Event &event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<WindowCloseEvent>(
      GS_BIND_EVENT_FN(Application::OnWindowClose));

  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
    (*--it)->OnEvent(event);
    // If we mark the event as handled, there is no need to propagate it down to
    // the layers.
    if (event.m_Handled) {
      break;
    }
  }
}

bool Application::OnWindowClose(WindowCloseEvent &event) {
  m_Running = false;
  return true;
}

void Application::Run() {
  while (m_Running) {
    glClearColor(0.1f, 0.1f, 0.1f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    m_Shader->Bind();
    glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT,
                   nullptr);

    for (Layer *layer : m_LayerStack) {
      layer->OnUpdate();
    }

    m_ImGuiLayer->Begin();
    for (Layer *layer : m_LayerStack) {
      layer->OnImGuiRender();
    }
    m_ImGuiLayer->End();

    m_Window->OnUpdate();
  }
}
} // namespace Genesis
