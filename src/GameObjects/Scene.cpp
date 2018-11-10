#include "GameObjects/Scene.hpp"


Scene::Scene() :
    _cameras(MAX_CAMERAS)
{
    this->_components.push_back(new Transform());

    for (unsigned i = 0; i < MAX_CAMERAS; ++i) {
        this->_cameras[i] = new Camera(this);
    }
    std::cout << "Create GameObject Scene" << '\n';
}

Scene::Scene(unsigned id, std::string name) :
    Scene()
{
    this->_id = id;
    this->_name = name;
    std::cout << "Create GameObject Scene" << '\n';
}

Scene::~Scene() {
    ;
}
