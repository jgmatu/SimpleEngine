#include "Systems/Keyboard.hpp"


Keyboard::Keyboard()
{
    std::string keys = "1234567890qwertyuioopasdfghjklzxcvbnm"\
        "QWERTYUIOPASDFGHJKLZXCVBNM";

    for(std::string::size_type i = 0; i < keys.size(); ++i) {
        _keys[std::string(1, keys[i])] = false;
    }
}

Keyboard::~Keyboard()
{

}

void Keyboard::init(Scene *scene)
{

}

void Keyboard::update(float dt, Scene *scene)
{

}

void Keyboard::sendMessage(Message *msg)
{

}

bool Keyboard::isKeyPressed(std::string key)
{
    std::map<std::string, bool>::iterator it;
    it = _keys.find(key);
    if (it == _keys.end()) {
        std::cerr << "The key " << key << " is not mapped" << '\n';
        throw;
    }
    return it->second;
}

void Keyboard::pressKey(std::string key)
{
    std::map<std::string, bool>::iterator it;
    it = _keys.find(key);
    if (it == _keys.end()) {
        std::cerr << "The key " << key << " is not mapped" << '\n';
        throw;
    }
    it->second = true;
}
