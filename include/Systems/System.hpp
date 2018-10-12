#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>

#include "GameObjects/Scene.hpp"
#include "Messages/Message.hpp"

class System {

public:

    // All systems need a virtual destructor to have their destructor called
    virtual ~System() {};

    // It's good practice to separate the construction and initialization code.
    virtual void init(Scene *scene) = 0;

    // All systems must update each game loop...
    virtual void update(float dt, Scene *scene) = 0;

    // This recieves any messages sent to the core engine in Engine.cpp
    virtual void sendMessage (Message *msg) = 0;

};

#endif
