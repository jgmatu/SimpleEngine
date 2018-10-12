#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <iostream>
#include <string>

#include "GameObjects/GameObject.hpp"
#include "Components/Material.hpp"
#include "Mesh/MeshRender.hpp"
#include "Mesh/Mesh.hpp"

class ObjectFactory {

public:

    ObjectFactory();
    ~ObjectFactory();

    void addGameObject(GameObject *gameObject);
    GameObject* getGameObject(unsigned id);
    std::vector<GameObject*> getListGameObjects();
    void generateDemoObjects();
    unsigned size();
    Mesh* getCubeMesh();


private:

    std::vector<GameObject*> _GameObjects;

};

#endif // OBJECT_FACTORY_H
