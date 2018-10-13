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
    Camera *camera = new Camera();
    camera->translate("(0, 0, -10)");

    GameObject* cube1 = new GameObject(1, " *** cube *** ");
    cube1->translate("(0, 0, 0)");

    MeshRender *meshRender = new MeshRender();
    Program *program = new Program("./glsl/vertex.glsl", "./glsl/fragments.glsl");
    Material *material = new Material(meshRender, program);

    meshRender->addMesh(getCubeMesh());
    cube1->addComponent(material);

    _GameObjects.push_back(camera);
    _GameObjects.push_back(cube1);
/*
    GameObject *cube2 = new GameObject(2, " *** cube *** ");
    _GameObjects.push_back(cube2);

    GameObject *cube3 = new GameObject(3, " *** cube *** ");
    _GameObjects.push_back(cube3);

    GameObject *cube4 = new GameObject(4, " *** cube *** ");
    cube3->_gameObjects.push_back(cube4);

    GameObject *cube5 = new GameObject(5, " *** cube *** ");
    cube3->_gameObjects.push_back(cube5);

    GameObject *cube6 = new GameObject(6, " *** cube *** ");
    cube4->_gameObjects.push_back(cube6);

    GameObject *cube7 = new GameObject(7, " *** cube *** ");
    cube6->_gameObjects.push_back(cube7);
*/
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
