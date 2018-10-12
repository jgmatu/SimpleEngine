#include "Engine.hpp"

Engine::Engine() :
    _systems()
{
    std::cout << "Open openGL Glad Context..." << '\n';
    std::cout << "Init windows system glfws..." << '\n';

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
    std::cout << "Exit system windows..." << '\n';
    std::cout << "Close OpenGL glad Context" << '\n';
}

void Engine::init() {
    std::cout << "Iniciar Engine!!" << '\n';
    GameObject *gameObject = _scene->getGameObject(6);
    if (gameObject != nullptr) {
        std::cout << "Game Object found! " << gameObject->_id << " " << gameObject->_name << '\n';
    } else {
        std::cout << "Game object not found..." << '\n';
    }
}

void Engine::add(System *sys) {
    std::cout << "Add System..." << '\n';
    _systems.push_back(sys);
};

void Engine::add(GameObject *gameObject) {
    _scene->addGameObject(gameObject);
}

void Engine::update(float dt) {
    for (unsigned i = 0; i < _systems.size(); ++i) {
        _systems[i]->update(dt, _scene);
    }
};

void Engine::mainLoop() {
    for (;;) {
        break;
    }
};
