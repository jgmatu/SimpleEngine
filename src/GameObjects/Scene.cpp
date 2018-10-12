#include "GameObjects/Scene.hpp"


Scene::Scene() :
    GameObject::GameObject()
{
    std::cout << "Creating Scene..." << '\n';
}

Scene::Scene(unsigned id, std::string name) :
    GameObject::GameObject(id, name)
{
    std::cout << "Creating Scene..." << _id << name << '\n';
}

Scene::~Scene() {
    std::cout << "Detele Scene..." << '\n';
}
