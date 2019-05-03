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
#include "Components/SkyBox.hpp"
#include "Operations/Movement.hpp"

#include "Model/Model.hpp"
#include "Model/Mesh.hpp"

#include <math.h>

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
    void addSceneLigths(Material *material);

    std::vector<Mesh*> getVerticesRenderBufferTexture();

    Mesh* getMeshFromVerticesPosTex(std::vector<float> vertices, __Texture__ texture);
    Mesh* getPlantMesh(std::string texture_diffuse);
    Mesh* getPlaneMesh();
    Mesh* getCubeMesh();
    Mesh* getSphereMesh(std::string filename);
    Mesh* getSkyBox();

    void solarSystem();
    void simulation1();
    void wallNormalMapping();

    std::vector<GameObject*> _GameObjects;
};

#endif // OBJECT_FACTORY_H
