#include "Systems/Keyboard.hpp"


Keyboard::Keyboard()
{
    std::string keys = "1234567890qwertyuiopasdfghjklzxcvbnm"\
        "QWERTYUIOPASDFGHJKLZXCVBNM!ª!\"·$&/()=?¿_:><,..-;: \\";

    for(std::string::size_type i = 0; i < keys.size(); ++i) {
        _keys_reguarls[std::string(1, keys[i])] = false;
    }
}

Keyboard::~Keyboard()
{
    Keyboard::instance = nullptr;
    std::cout << "Delete reference to keyboard :)" << '\n';
}

bool Keyboard::isKeyPressed(std::string key)
{
    std::map<std::string, bool>::const_iterator it;

    it = _keys_reguarls.find(key);
    return it != _keys_reguarls.end() && it->second;
}


bool Keyboard::isKeyPressed(int32_t key)
{
    std::map<int32_t, bool>::const_iterator it;

    it = _keys_specials.find(key);
    return it != _keys_specials.end() && it->second;
}

void Keyboard::pressKey(std::string key, bool pressed)
{
    std::map<std::string, bool>::iterator it = _keys_reguarls.find(key);

    if (it != _keys_reguarls.end()){
        it->second = pressed;
    }
}

void Keyboard::pressKey(int32_t key, bool pressed)
{
    std::map<int32_t, bool>::iterator it = _keys_specials.find(key);

    if (it != _keys_specials.end()){
        it->second = pressed;
    }
}

void Keyboard::CallBackCharacters(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    const char* name = glfwGetKeyName(key, 0);
    bool pressed = action == GLFW_PRESS || action == GLFW_REPEAT;

    if (name) {
        Keyboard::instance->pressKey(std::string(name), pressed);
    } else {
        Keyboard::instance->pressKey(key, pressed);
    }

    // Exit engine...
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
