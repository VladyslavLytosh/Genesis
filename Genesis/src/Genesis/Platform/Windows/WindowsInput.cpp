#include "gspch.h"

#include "Genesis/Application.h"
#include "WindowsInput.h"
#include <GLFW/glfw3.h>

namespace Genesis
{
    std::unique_ptr<Input> Input::s_Instance = std::make_unique<WindowsInput>();

    bool WindowsInput::IsKeyPressedImpl(KeyCode keycode) const
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetActualWindow());
        const int state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(MouseCode button) const
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetActualWindow());
        const int state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl() const
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetActualWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return {float(xPos), float(yPos)};
    }

    float WindowsInput::GetMouseXImpl() const
    {
        auto [x, y] = GetMousePositionImpl();
        return x;
    }

    float WindowsInput::GetMouseYImpl() const
    {
        auto [x, y] = GetMousePositionImpl();
        return y;
    }
}  // namespace Genesis