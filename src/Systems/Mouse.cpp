#include "Systems/Mouse.hpp"

void Mouse::CursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
{
    std::cout << "xpos " << xpos << '\n';
    std::cout << "ypos " << ypos << '\n';
}

void Mouse::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        std::cout << "Pressed Right!" << '\n';
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "Pressed Left!" << '\n';
    }
}

void Mouse::CursorEnterAreaCallback(GLFWwindow *window, int entered)
{
    ;
}
