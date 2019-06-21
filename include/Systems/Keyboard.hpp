#ifndef SYSTEM_KEYBOARD_H
#define SYSTEM_KEYBOARD_H

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Messages/Message.hpp"

class Keyboard {

public:

    inline static Keyboard *instance;

    static Keyboard* getInstance()
    {
        if (!Keyboard::instance) {
            Keyboard::instance = new Keyboard();
        }
        return Keyboard::instance;
    }
    ~Keyboard();

    bool isKeyPressed(std::string key);
    bool isKeyPressed(int32_t key);

    void pressKey(std::string key, bool pressed);
    void pressKey(int key, bool pressed);

    static void CallBackCharacters(GLFWwindow *window, int key, int scancode, int action, int mods);

private:

    Keyboard();

    Keyboard(Keyboard const&) = delete;
    void operator=(Keyboard const&)  = delete;

    std::map<std::string, bool> _keys_reguarls;
    std::map<int32_t, bool> _keys_specials = {
        {GLFW_KEY_UNKNOWN, false},
        {GLFW_KEY_ESCAPE, false},
        {GLFW_KEY_ENTER, false},
        {GLFW_KEY_TAB, false},
        {GLFW_KEY_BACKSPACE, false},
        {GLFW_KEY_INSERT, false},
        {GLFW_KEY_DELETE, false},
        {GLFW_KEY_RIGHT, false},
        {GLFW_KEY_LEFT, false},
        {GLFW_KEY_DOWN, false},
        {GLFW_KEY_UP, false},
        {GLFW_KEY_PAGE_UP, false},
        {GLFW_KEY_PAGE_DOWN, false},
        {GLFW_KEY_HOME, false},
        {GLFW_KEY_END, false},
        {GLFW_KEY_CAPS_LOCK, false},
        {GLFW_KEY_SCROLL_LOCK, false},
        {GLFW_KEY_NUM_LOCK, false},
        {GLFW_KEY_PRINT_SCREEN, false},
        {GLFW_KEY_PAUSE, false},
        {GLFW_KEY_F1, false},
        {GLFW_KEY_F2, false},
        {GLFW_KEY_F3, false},
        {GLFW_KEY_F4, false},
        {GLFW_KEY_F5, false},
        {GLFW_KEY_F6, false},
        {GLFW_KEY_F7, false},
        {GLFW_KEY_F8, false},
        {GLFW_KEY_F9, false},
        {GLFW_KEY_F10, false},
        {GLFW_KEY_F11, false},
        {GLFW_KEY_F12, false},
        {GLFW_KEY_LEFT_SHIFT, false},
        {GLFW_KEY_LEFT_CONTROL, false},
        {GLFW_KEY_LEFT_ALT, false},
        {GLFW_KEY_LEFT_SUPER, false},
        {GLFW_KEY_RIGHT_SHIFT, false},
        {GLFW_KEY_RIGHT_CONTROL, false},
        {GLFW_KEY_RIGHT_ALT, false},
        {GLFW_KEY_RIGHT_SUPER, false},
        {GLFW_KEY_MENU, false},
    };
};

#endif // Keyboard_IO_H
