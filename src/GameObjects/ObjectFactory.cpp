#include "GameObjects/ObjectFactory.hpp"

ObjectFactory::ObjectFactory() :
    _GameObjects()
{
    std::cout << "Creating Factory Objects..." << '\n';
}

ObjectFactory::~ObjectFactory() {
    std::cout << "Delete All Game Objects!" << '\n';
    for (unsigned i = 0; i < _GameObjects.size(); ++i) {
        delete _GameObjects[i];
    }
}

void ObjectFactory::addGameObject(GameObject *gameObject) {
    _GameObjects.push_back(gameObject);
};

GameObject* ObjectFactory::getGameObject(unsigned id) {
    return _GameObjects[id];
}

std::vector<GameObject*> ObjectFactory::getListGameObjects() {
    return _GameObjects;
}

void ObjectFactory::generateDemoObjects() {
    GameObject* cube1 = new GameObject(1, "*** cube ***");
    MeshRender *meshRender = new MeshRender();
    Program *program = new Program("./glsl/vertex.glsl", "./glsl/fragments.glsl");
    Material *material = new Material(meshRender, program);

    meshRender->addMesh(getCubeMesh());
    cube1->addComponent(material);
}

Mesh* ObjectFactory::getCubeMesh() {
    Mesh *mesh = new Mesh(1);

    mesh->_vertexPos = std::vector<float>();
    mesh->_vertexNormal = std::vector<float>();
    mesh->_vertexTexCoord = std::vector<float>();
    mesh->_triangleIndex = std::vector<unsigned>();
    mesh->_NTriangleIndex = 0;

    return mesh;
}

unsigned ObjectFactory::size() {
    return _GameObjects.size();
}
