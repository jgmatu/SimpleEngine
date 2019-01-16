#include "GameObjects/GameObject.hpp"

GameObject::GameObject() :
    _id(13333333),
    _name("?"),
    _components(),
    _gameObjects()
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
}

Component* GameObject::getComponent(TypeComp type) const {
    Component* search = nullptr;

    for (unsigned i = 0; !search && i < _components.size(); ++i) {
        if (_components[i]->_type == type) {
            search = _components[i];
        }
    }
    return search;
}

void GameObject::addComponent(Component *component) {
    _components.push_back(component);
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

    for (unsigned i = 0; !search && i < _gameObjects.size(); ++i) {
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

void GameObject::scale(glm::vec3 vec3) {
    Component *component = getComponent(TypeComp::TRANSFORM);

    if (Transform *tf = dynamic_cast<Transform*>(component)) {
        tf->scale(vec3);
    }
}

void GameObject::translate(glm::vec3 vec3) {
    Component *component = getComponent(TypeComp::TRANSFORM);

    if (Transform *tf = dynamic_cast<Transform*>(component)) {
        tf->translate(vec3);
    }
}

void GameObject::rotate(glm::vec3 vec3, glm::quat quat) {
    Component *component = getComponent(TypeComp::TRANSFORM);

    if (Transform *tf = dynamic_cast<Transform*>(component)) {
        tf->rotate(vec3, quat);
    }
}

void GameObject::rotate(glm::vec3 vec3, float angle) {
    Component *component = getComponent(TypeComp::TRANSFORM);

    if (Transform *tf = dynamic_cast<Transform*>(component)) {
        tf->rotate(vec3, angle);
    }
}

std::ostream& operator<<(std::ostream& os, const GameObject& gameObject) {
    os << gameObject._name << std::endl;
    Component *component = gameObject.getComponent(TypeComp::TRANSFORM);
    if (Transform *tf = dynamic_cast<Transform*>(component)) {
        os << (*tf);
    }

    component = gameObject.getComponent(TypeComp::MATERIAL);
    if (Material *material = dynamic_cast<Material*>(component)) {
        os << (*material);
    }
    return os;
}
