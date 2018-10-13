#include "GameObjects/GameObject.hpp"

GameObject::GameObject() :
    _components(),
    _gameObjects(),
    _id(13333333),
    _name("?")
{
    _components.push_back(new Transform());
}

GameObject::GameObject(unsigned id, std::string name) :
    GameObject()
{
    this->_id = id;
    this->_name = name;
}

GameObject::~GameObject() {
    for (unsigned i = 0; i < _gameObjects.size(); ++i) {
        delete _gameObjects[i];
    }
    for (unsigned i = 0; i < _components.size(); ++i) {
        delete _components[i];
    }
}

Component* GameObject::getComponent(TypeComp type) {
    Component *search = nullptr;

    for (unsigned i = 0; i < _components.size() && search == nullptr; ++i) {
        if (_components[i]->_type == type) {
            search = _components[i];
        }
    }
    return search;
}

void GameObject::addComponent(Component *comp) {
    _components.push_back(comp);
}

bool GameObject::hasComponent(TypeComp type) {
    for (unsigned i = 0; i < _components.size(); ++i) {
        if (_components[i]->_type == type) {
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
        _gameObjects[i]->hasGameObject(id);
    }
    return false;
}

std::vector<unsigned> GameObject::getKeysObjects() {
    std::vector<unsigned> keys;

    for (unsigned i = 0; i < _gameObjects.size(); ++i) {
        std::vector<unsigned> subkeys = _gameObjects[i]->getKeysObjects();

        keys.insert(keys.end(), subkeys.begin(), subkeys.end());
        keys.push_back(_gameObjects[i]->_id);
    }
    return keys;
}

void GameObject::scale(std::string vec3) {
    Component *component = getComponent(TypeComp::TRANSFORM);

    if (Transform *tf =  dynamic_cast<Transform*>(component)) {
        tf->scale(vec3);
    }
}

void GameObject::translate(std::string vec3) {
    Component *component = getComponent(TypeComp::TRANSFORM);

    if (Transform *tf =  dynamic_cast<Transform*>(component)) {
        tf->translate(vec3);
    }
}

void GameObject::rotate(std::string vec3, std::string quad) {
    Component *component = getComponent(TypeComp::TRANSFORM);

    if (Transform *tf =  dynamic_cast<Transform*>(component)) {
        tf->rotate(vec3, quad);
    }
}
