#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <iostream>

#include "Components/Component.hpp"
#include "Components/Transform.hpp"

class GameObject {

public:

    GameObject();
    GameObject(unsigned id, std::string _name);
    ~GameObject();

    Component* getComponent(unsigned id);
    void addComponent(Component *comp);
    bool hasComponent(unsigned id);

    bool hasGameObject(unsigned id);

    GameObject* getGameObject(unsigned id);

    void addGameObject(GameObject *gameObject);

protected:

    friend class Engine;

    unsigned _id;
    std::string _name;

    std::vector<GameObject*> _gameObjects;
    std::vector<Component*> _components;

};

#endif
