#ifndef SYSTEM_KEYBOARD_H
#define SYSTEM_KEYBOARD_H

#include <vector>
#include <iostream>
#include <string>
#include <memory>

#include "Systems/System.hpp"
#include "Messages/Message.hpp"

class Keyboard : public System {

public:

     Keyboard();
    ~Keyboard();

    void init(Scene *scene);
    void update(float dt, Scene *scene);
    void sendMessage (Message *msg);

    bool isKeyPressed(std::string key);
    void pressKey(std::string key);

private:
    std::map<std::string, bool> _keys;
};

#endif // Keyboard_IO_H
