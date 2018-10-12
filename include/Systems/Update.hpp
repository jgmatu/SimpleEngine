#ifndef SYSTEM_UPDATE_H
#define SYSTEM_UPDATE_H

#include <vector>
#include <iostream>
#include <string>

#include "Systems/System.hpp"
#include "GameObjects/GameObject.hpp"
#include "Messages/Message.hpp"

class Update : public System {

public:

     Update();
    ~Update();

    void init(std::vector<GameObject*> _GameObjects);
    void update(float dt, std::vector<GameObject*> _GameObjects);
    void sendMessage (Message *msg);

private:

};

#endif // SYSTEM_UPDATE_H
