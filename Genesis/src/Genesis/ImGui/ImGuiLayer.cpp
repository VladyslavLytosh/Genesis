#include "gspch.h"

#include "ImGuiLayer.h"

#include "Genesis/Application.h"
#include <imgui.h>
#include "Genesis/Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Genesis/Input.h"

// TEMP
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Genesis/KeyCodes.h"

namespace Genesis
{
	static ImGuiKey GenesisKeysToImGuiKeys(int key);
	static const char* GetClipboardText(void* user_data);
	static void SetClipboardText(void* user_data, const char* text);

    static void UpdateKeyModifiers();

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
        IMGUI_CHECKVERSION();
		ImGui::CreateContext();
        ImGui::StyleColorsClassic();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.SetClipboardTextFn = SetClipboardText;
        io.GetClipboardTextFn = GetClipboardText;

		ImGui_ImplOpenGL3_Init("#version 460 core");
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		const Application& app = Application::Get();
		io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), 
            static_cast<float>(app.GetWindow().GetHeight()));

		const float time = static_cast<float>(glfwGetTime());
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseMovedEvent>(GS_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseButtonPressedEvent>(GS_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(GS_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(GS_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(GS_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(GS_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(GS_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(event.GetX(), event.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (event.GetMouseButton() >= 0 && event.GetMouseButton() < ImGuiMouseButton_COUNT)
		{
            UpdateKeyModifiers();

			io.AddMouseButtonEvent(event.GetMouseButton(), true);
		}

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (event.GetMouseButton() >= 0 && event.GetMouseButton() < ImGuiMouseButton_COUNT)
		{
			io.AddMouseButtonEvent(event.GetMouseButton(), false);
		}

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(event.GetXOffset(), event.GetYOffset());

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& event)
	{
        ImGuiIO& io = ImGui::GetIO();
        ImGuiKey imgui_key = GenesisKeysToImGuiKeys(event.GetKeyCode());

        UpdateKeyModifiers();

        io.AddKeyEvent(imgui_key, true);

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey imgui_key = GenesisKeysToImGuiKeys(event.GetKeyCode());
        io.AddKeyEvent(imgui_key, false);

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& event)
	{
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter(event.GetKeyCode());

        return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
	{
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(static_cast<float>(event.GetWidth()), static_cast<float>(event.GetHeight()));
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, static_cast<GLsizei>(event.GetWidth()), static_cast<GLsizei>(event.GetHeight()));

        return false;
	}
}

ImGuiKey Genesis::GenesisKeysToImGuiKeys(int key)
{
    switch (key)
    {
    case Key::Tab: return ImGuiKey_Tab;
    case Key::Left: return ImGuiKey_LeftArrow;
    case Key::Right: return ImGuiKey_RightArrow;
    case Key::Up: return ImGuiKey_UpArrow;
    case Key::Down: return ImGuiKey_DownArrow;
    case Key::Page_up: return ImGuiKey_PageUp;
    case Key::Page_down: return ImGuiKey_PageDown;
    case Key::Home: return ImGuiKey_Home;
    case Key::End: return ImGuiKey_End;
    case Key::Insert: return ImGuiKey_Insert;
    case Key::Delete: return ImGuiKey_Delete;
    case Key::Backspace: return ImGuiKey_Backspace;
    case Key::Space: return ImGuiKey_Space;
    case Key::Enter: return ImGuiKey_Enter;
    case Key::Escape: return ImGuiKey_Escape;
    case Key::Apostrophe: return ImGuiKey_Apostrophe;
    case Key::Comma: return ImGuiKey_Comma;
    case Key::Minus: return ImGuiKey_Minus;
    case Key::Period: return ImGuiKey_Period;
    case Key::Slash: return ImGuiKey_Slash;
    case Key::Semicolon: return ImGuiKey_Semicolon;
    case Key::Equal: return ImGuiKey_Equal;
    case Key::Left_bracket: return ImGuiKey_LeftBracket;
    case Key::Backslash: return ImGuiKey_Backslash;
    case Key::Right_bracket: return ImGuiKey_RightBracket;
    case Key::Grave_accent: return ImGuiKey_GraveAccent;
    case Key::Caps_lock: return ImGuiKey_CapsLock;
    case Key::Scroll_lock: return ImGuiKey_ScrollLock;
    case Key::Num_lock: return ImGuiKey_NumLock;
    case Key::Print_screen: return ImGuiKey_PrintScreen;
    case Key::Pause: return ImGuiKey_Pause;
    case Key::KP0: return ImGuiKey_Keypad0;
    case Key::KP1: return ImGuiKey_Keypad1;
    case Key::KP2: return ImGuiKey_Keypad2;
    case Key::KP3: return ImGuiKey_Keypad3;
    case Key::KP4: return ImGuiKey_Keypad4;
    case Key::KP5: return ImGuiKey_Keypad5;
    case Key::KP6: return ImGuiKey_Keypad6;
    case Key::KP7: return ImGuiKey_Keypad7;
    case Key::KP8: return ImGuiKey_Keypad8;
    case Key::KP9: return ImGuiKey_Keypad9;
    case Key::KPDecimal: return ImGuiKey_KeypadDecimal;
    case Key::KPDivide: return ImGuiKey_KeypadDivide;
    case Key::KPMultiply: return ImGuiKey_KeypadMultiply;
    case Key::KPSubtract: return ImGuiKey_KeypadSubtract;
    case Key::KPAdd: return ImGuiKey_KeypadAdd;
    case Key::KPEnter: return ImGuiKey_KeypadEnter;
    case Key::KPEqual: return ImGuiKey_KeypadEqual;
    case Key::Left_Shift: return ImGuiKey_LeftShift;
    case Key::Left_Control: return ImGuiKey_LeftCtrl;
    case Key::Left_Alt: return ImGuiKey_LeftAlt;
    case Key::Left_Super: return ImGuiKey_LeftSuper;
    case Key::Right_Shift: return ImGuiKey_RightShift;
    case Key::Right_Control: return ImGuiKey_RightCtrl;
    case Key::Right_Alt: return ImGuiKey_RightAlt;
    case Key::Right_Super: return ImGuiKey_RightSuper;
    case Key::Menu: return ImGuiKey_Menu;
    case Key::N0: return ImGuiKey_0;
    case Key::N1: return ImGuiKey_1;
    case Key::N2: return ImGuiKey_2;
    case Key::N3: return ImGuiKey_3;
    case Key::N4: return ImGuiKey_4;
    case Key::N5: return ImGuiKey_5;
    case Key::N6: return ImGuiKey_6;
    case Key::N7: return ImGuiKey_7;
    case Key::N8: return ImGuiKey_8;
    case Key::N9: return ImGuiKey_9;
    case Key::A: return ImGuiKey_A;
    case Key::B: return ImGuiKey_B;
    case Key::C: return ImGuiKey_C;
    case Key::D: return ImGuiKey_D;
    case Key::E: return ImGuiKey_E;
    case Key::F: return ImGuiKey_F;
    case Key::G: return ImGuiKey_G;
    case Key::H: return ImGuiKey_H;
    case Key::I: return ImGuiKey_I;
    case Key::J: return ImGuiKey_J;
    case Key::K: return ImGuiKey_K;
    case Key::L: return ImGuiKey_L;
    case Key::M: return ImGuiKey_M;
    case Key::N: return ImGuiKey_N;
    case Key::O: return ImGuiKey_O;
    case Key::P: return ImGuiKey_P;
    case Key::Q: return ImGuiKey_Q;
    case Key::R: return ImGuiKey_R;
    case Key::S: return ImGuiKey_S;
    case Key::T: return ImGuiKey_T;
    case Key::U: return ImGuiKey_U;
    case Key::V: return ImGuiKey_V;
    case Key::W: return ImGuiKey_W;
    case Key::X: return ImGuiKey_X;
    case Key::Y: return ImGuiKey_Y;
    case Key::Z: return ImGuiKey_Z;
    case Key::F1: return ImGuiKey_F1;
    case Key::F2: return ImGuiKey_F2;
    case Key::F3: return ImGuiKey_F3;
    case Key::F4: return ImGuiKey_F4;
    case Key::F5: return ImGuiKey_F5;
    case Key::F6: return ImGuiKey_F6;
    case Key::F7: return ImGuiKey_F7;
    case Key::F8: return ImGuiKey_F8;
    case Key::F9: return ImGuiKey_F9;
    case Key::F10: return ImGuiKey_F10;
    case Key::F11: return ImGuiKey_F11;
    case Key::F12: return ImGuiKey_F12;
    case Key::F13: return ImGuiKey_F13;
    case Key::F14: return ImGuiKey_F14;
    case Key::F15: return ImGuiKey_F15;
    case Key::F16: return ImGuiKey_F16;
    case Key::F17: return ImGuiKey_F17;
    case Key::F18: return ImGuiKey_F18;
    case Key::F19: return ImGuiKey_F19;
    case Key::F20: return ImGuiKey_F20;
    case Key::F21: return ImGuiKey_F21;
    case Key::F22: return ImGuiKey_F22;
    case Key::F23: return ImGuiKey_F23;
    case Key::F24: return ImGuiKey_F24;
    default: return ImGuiKey_None;
    }
}

const char* Genesis::GetClipboardText(void* user_data)
{
    return glfwGetClipboardString((GLFWwindow*)user_data);
}

void Genesis::SetClipboardText(void* user_data, const char* text)
{
    glfwSetClipboardString((GLFWwindow*)user_data, text);
}

void Genesis::UpdateKeyModifiers()
{
    ImGuiIO& io = ImGui::GetIO();
    io.AddKeyEvent(ImGuiMod_Ctrl, Input::IsKeyPressed(Key::Left_Control) || Input::IsKeyPressed(Key::Right_Control));
    io.AddKeyEvent(ImGuiMod_Shift, Input::IsKeyPressed(Key::Left_Shift) || Input::IsKeyPressed(Key::Right_Shift));
    io.AddKeyEvent(ImGuiMod_Alt, Input::IsKeyPressed(Key::Left_Alt) || Input::IsKeyPressed(Key::Right_Alt));
    io.AddKeyEvent(ImGuiMod_Super, Input::IsKeyPressed(Key::Left_Super) || Input::IsKeyPressed(Key::Right_Super));
}