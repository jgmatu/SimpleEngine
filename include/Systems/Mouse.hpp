#ifndef MOUSE_IO_H
#define MOUSE_IO_H

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Messages/Message.hpp"


class Mouse {

public:

    inline static Mouse *instance;

    static Mouse* getInstance()
    {
        if (!instance) {
            Mouse::instance = new Mouse();
        }
        return Mouse::instance;
    }

    ~Mouse()
    {
        Mouse::instance = nullptr;
    };

    glm::mat4 rotate();

    static void CursorPositionCallback(GLFWwindow *window, double xpos, double ypos);
    static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    static void CursorEnterAreaCallback(GLFWwindow *window, int entered);

    double _x, _y;
    bool _rClick, _lClick;

private:

    Mouse();
    Mouse(Mouse const&) = delete;
    void operator=(Mouse const&)  = delete;
};

#endif
