#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <iostream>

#include "Components/Component.hpp"

class GameObject {

public:

    GameObject();
    ~GameObject();

protected:

    std::vector<GameObject*> _GameObjects;
    std::vector<Component*> _Components;

};

#endif
