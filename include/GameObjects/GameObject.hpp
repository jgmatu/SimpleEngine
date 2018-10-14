#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <iostream>

#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include "Constants/TypeComp.hpp"

class GameObject {

public:

    GameObject();
    GameObject(unsigned id, std::string _name);
    virtual ~GameObject();

    Component* getComponent(TypeComp type);
    void addComponent(Component *comp);
    bool hasComponent(TypeComp type);

    GameObject* getGameObject(unsigned id);
    bool hasGameObject(unsigned id);
    void addGameObject(GameObject *gameObject);

    std::vector<unsigned> getKeysObjects();

    void scale(std::string vec3);
    void translate(std::string vec3);
    void rotate(std::string vec3, std::string quad);

protected:

    unsigned _id;
    std::string _name;

    std::vector<GameObject*> _gameObjects;
    std::vector<Component*> _components;

};

#endif
