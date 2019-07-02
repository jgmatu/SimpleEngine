#include <iostream>
#include <exception>

#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameObjects/GameObject.hpp"
#include "Components/Camera.hpp"
#include "Components/Material.hpp"
#include "Components/SkyBox.hpp"

#include "Geometries/Cube.hpp"
#include "Geometries/Sphere.hpp"
#include "Geometries/Plane.hpp"

#include "Engine.hpp"

class Example : public Component {

public:

    Example()
    {
        ;
    }

    ~Example()
    {

    }

    void start()
    {
        ;
    }

    void update()
    {
        ;
    }

    void awakeStart()
    {
        ;
    }

};

class ExampleMove : public Component {

public:

    uint32_t counter;

    ExampleMove()
    {
        counter = 0;
    }

    ~ExampleMove()
    {
        ;
    }

    void start()
    {
        ;
    }

    void update()
    {
        ;
    }

    void awakeStart()
    {
        ;
    }
};

GameObject *getCube(std::string name)
{
    ;
}

std::vector<Light*> getLigthPoints()
{
    ;
}

void addLigths(Scene *scene)
{
    ;
}

Scene* sceneSimulation()
{
    ;
}

int main(int argc, char* argv[]) {
    Engine *engine = nullptr;

    try {
        Scene *scene = sceneSimulation();
        engine = new Engine(scene);
        engine->init();
        engine->mainLoop();
    } catch (std::exception &ex) {
        std::cerr << "Engine Error : " << ex.what() << '\n';
    } catch (...) {
        std::cerr << "Engine fatal!" << '\n';
    }
    if (engine) {
        delete engine;
    }
}
