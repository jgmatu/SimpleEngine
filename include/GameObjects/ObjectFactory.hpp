#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameObjects/GameObject.hpp"

#include "Components/Camera.hpp"
#include "Components/Material.hpp"
#include "Components/Light.hpp"

#include "Model/Model.hpp"
#include "Model/Mesh.hpp"

#include <math.h>

class ObjectFactory {

public:

    ObjectFactory();
    ~ObjectFactory();

    GameObject* getGameObject(unsigned id);
    void addGameObject(GameObject *gameObject);
    unsigned size();

    void generateDemoObjects();

private:

    Mesh* getPlaneMesh();
    Mesh* getCubeMesh();
    Mesh* getSphereMesh();

    std::vector<GameObject*> _GameObjects;
};

#endif // OBJECT_FACTORY_H
