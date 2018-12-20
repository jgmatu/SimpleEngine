#include "GameObjects/Scene.hpp"


Scene::Scene() :
    GameObject::GameObject(),
    _cameras(MAX_CAMERAS)
{
    for (unsigned i = 0; i < MAX_CAMERAS; ++i) {
        this->_cameras[i] = new Camera(this);
    }
    std::cout << "Create GameObject Scene" << '\n';
}

Scene::Scene(unsigned id, std::string name) :
    GameObject::GameObject(id, name),
    _cameras(MAX_CAMERAS)
{
    for (unsigned i = 0; i < MAX_CAMERAS; ++i) {
        this->_cameras[i] = new Camera(this);
    }
    std::cout << "Create GameObject Scene" << '\n';
}

Scene::~Scene() {
    for (unsigned i = 0; i < MAX_CAMERAS; ++i) {
        delete this->_cameras[i];
    }
}
