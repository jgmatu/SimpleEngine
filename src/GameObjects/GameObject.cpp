#include "GameObjects/GameObject.hpp"

GameObject::GameObject() :
    _components(),
    _gameObjects(),
    _id(13333333),
    _name("?")
{
    std::cout << "Creating Basic Game Object..." << '\n';
    _components.push_back(new Transform());
}

GameObject::GameObject(unsigned id, std::string name) :
    GameObject()
{
    this->_id = id;
    this->_name = name;
    std::cout << "Creating Game Object..."  << "id: " << _id << "name : " << _name << '\n';
}

GameObject::~GameObject() {
    for (unsigned i = 0; i < _gameObjects.size(); ++i) {
        delete _gameObjects[i];
    }
    for (unsigned i = 0; i < _components.size(); ++i) {
        delete _components[i];
    }
}

Component* GameObject::getComponent(unsigned id) {
    Component *search = nullptr;

    for (unsigned i = 0; i < _components.size() && search == nullptr; ++i) {
        if (_components[i]->_id == id) {
            search = _components[i];
        }
    }
    if (search == nullptr) {
        throw;
    }
    return search;
}

void GameObject::addComponent(Component *comp) {
    std::cout << "Added Component " << '\n';
    _components.push_back(comp);
}

bool GameObject::hasComponent(unsigned id) {
    for (unsigned i = 0; i < _components.size(); ++i) {
        if (_components[i]->_id == id) {
            return true;
        }
    }
    return false;
}

GameObject* GameObject::getGameObject(unsigned id) {
    GameObject *search = nullptr;

    for (unsigned i = 0; search == nullptr && i < _gameObjects.size(); ++i) {
        if (_gameObjects[i]->_id == id) {
            search = _gameObjects[i];
        } else {
            search = _gameObjects[i]->getGameObject(id);
        }
    }
    return search;
}

void GameObject::addGameObject(GameObject *gameObject) {
    _gameObjects.push_back(gameObject);
}

bool GameObject::hasGameObject(unsigned id) {
    for (unsigned i = 0; i < _gameObjects.size(); ++i) {
        if (id == _gameObjects[i]->_id) {
            return true;
        }
        _gameObjects[i]->hasComponent(id);
    }
    return false;
}
