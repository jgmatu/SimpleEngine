#ifndef SYSTEM_UPDATE_H
#define SYSTEM_UPDATE_H

#include <vector>
#include <iostream>
#include <string>
#include <memory>

#include "Systems/System.hpp"
#include "GameObjects/GameObject.hpp"
#include "Messages/Message.hpp"

class Update : public System {

public:

     Update();
    ~Update();

    void init(Scene *scene);
    void update(float dt, Scene *scene);
    void sendMessage (Message *msg);

private:

};

#endif // SYSTEM_UPDATE_H
