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
#include "Components/SkyBox.hpp"

#include "Geometries/Cube.hpp"
#include "Geometries/Sphere.hpp"
#include "Geometries/Plane.hpp"

#include <math.h>

class Mesh;

class ObjectFactory {

public:

    ObjectFactory();
    ~ObjectFactory();

    GameObject* getGameObject(unsigned id);
    std::vector<GameObject*> getGameObjects();

    void addGameObject(GameObject *gameObject);
    unsigned size();
    void generateDemoObjects();

private:

    void addSkyBox(std::string directory);

    // Basic skybox
    Mesh* getSkyBox();

    // Simulations... (Use of API Engine)
    void solarSystem();
    void simulation1();
    void wallNormalMapping();

    std::vector<GameObject*> _GameObjects;
};

#endif // OBJECT_FACTORY_H
