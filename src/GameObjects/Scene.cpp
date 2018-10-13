#include "GameObjects/Scene.hpp"


Scene::Scene() :
    GameObject::GameObject()
{
    std::cout << "Create GameObject Scene" << '\n';
}

Scene::Scene(unsigned id, std::string name) :
    GameObject::GameObject(id, name)
{
    std::cout << "Create GameObject Scene" << '\n';
}

Scene::~Scene() {
    ;
}
