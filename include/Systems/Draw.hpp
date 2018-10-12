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

    void init(Scene *scene);
    void update(float dt, Scene *scene);
    void sendMessage (Message *msg);
    
private:

};

#endif
