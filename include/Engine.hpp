#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>

#include "Systems/System.hpp"
#include "GameObjects/ObjectFactory.hpp"

class Engine {

public:

    Engine();
    ~Engine();

private:

    std::vector<System*> _systems;
    ObjectFactory *_objectFactory;

};

#endif // ENGINE_H
