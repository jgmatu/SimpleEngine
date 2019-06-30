#include "Systems/Mouse.hpp"

Mouse::Mouse()
{
    this->_x = 0;
    this->_y = 0;
};

glm::mat4 Mouse::rotate()
{
    //modulo 360° (1 turn), angles are expressed in degrees here.
//    float newAngleX = (orientation.getX() + angleX) % 360.0f;

    //modulo 360° (1 turn), angles are expressed in degrees here.
//    float newAngleY = (orientation.getY() + angleY) % 360.0f;

//    orientation.setX(newAngleX);
//    orientation.setY(newAngleY);
    return glm::mat4(1.0f);
}

void Mouse::CursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
{
    Mouse::instance->_x =  xpos;
    Mouse::instance->_y = -ypos;

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
    Mouse::instance->_rClick = button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS;
    Mouse::instance->_lClick = button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS;
}

void Mouse::CursorEnterAreaCallback(GLFWwindow *window, int entered)
{
    ;
}
