#ifndef ENGINE_H
#define ENGINE_H

#include <chrono>
#include <thread>
#include <iostream>
#include <string>

#include "Systems/System.hpp"
#include "GameObjects/ObjectFactory.hpp"
#include "GameObjects/Scene.hpp"

class Engine {

public:

    Engine();
    Engine(ObjectFactory *objectFactory);
    ~Engine();

    void init();
    void update(float dt);
    void mainLoop();
    void add(System *sys);
    void add(GameObject *gameObject);

private:

    std::vector<System*> _systems;
    Scene *_scene;

};

#endif // ENGINE_H
