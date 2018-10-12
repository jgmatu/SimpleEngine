#ifndef DRAW_H
#define DRAW_H

#include <vector>

#include "Systems/System.hpp"
#include "GameObjects/GameObject.hpp"
#include "Messages/Message.hpp"

class Draw : public System {

public:

    Draw();
    ~Draw();

    void init(std::vector<GameObject*> _GameObjects);
    void update(float dt, std::vector<GameObject*> _GameObjects);
    void sendMessage (Message *msg);

private:

};

#endif
