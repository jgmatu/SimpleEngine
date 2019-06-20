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
    std::cout << "Delete keyboard :)" << '\n';
}

bool Keyboard::isKeyPressed(std::string key)
{
    std::map<std::string, bool>::const_iterator it;

    it = _keys_reguarls.find(key);
    return it != _keys_reguarls.end() && it->second;
}

void Keyboard::pressKey(std::string key, bool pressed)
{
    std::map<std::string, bool>::iterator it;

    for (it = _keys_reguarls.begin(); it != _keys_reguarls.end(); ++it) {
        it->second = it->first.compare(key) == 0 && pressed;
    }
}

void Keyboard::pressKey(int32_t key, bool pressed)
{
    std::map<int32_t, bool>::iterator it;

    for (it = _keys_specials.begin(); it != _keys_specials.end(); ++it) {
        it->second = it->first == key && pressed;
    }
}
