#include "Engine.hpp"

Engine::Engine() :
    _systems()
{
    // OpengL Conext...
    // Init windows system glfws
    _scene = new Scene(0, "*** scene *** ");
}

Engine::Engine(ObjectFactory *objectFactory) :
    Engine::Engine()
{
    for (unsigned i = 0; i < objectFactory->size(); ++i) {
        this->add(objectFactory->getGameObject(i));
    }
}

Engine::~Engine() {
    for (unsigned i = 0; i < _systems.size(); ++i) {
        delete _systems[i];
    }
    delete _scene;
    // Exit system windows...
    // Close OpenGL glad Conext...
}

void Engine::init() {
    std::cout << "Iniciar Engine!!" << '\n';
    for (unsigned i = 0; i < _systems.size(); ++i) {
        _systems[i]->init(_scene);
    }
}

void Engine::add(System *sys) {
    _systems.push_back(sys);
}

void Engine::add(GameObject *gameObject) {
    _scene->addGameObject(gameObject);
}

void Engine::update(float dt) {
    for (unsigned i = 0; i < _systems.size(); ++i) {
        _systems[i]->update(dt, _scene);
    }
}

void Engine::mainLoop() {
    for (;;) {
        this->update(0);
        GameObject *cube = _scene->getGameObject(1);
        cube->translate("(0, 0, 1)");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
