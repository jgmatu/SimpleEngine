#include "GameObjects/Scene.hpp"

class Root : public Component {

private:

    bool wasPressed;

public: 

    Root()
    {
        wasPressed = false;
    }

    void update()
    {
        Scene *scene = this->_gObject->_scene;
        if (!scene) {
            std::cerr << "Scene not found!" << std::endl;
            throw;
        }
        bool isPressed = Keyboard::instance->isKeyPressed("x");
        if (!wasPressed && isPressed) {
            scene->changeCamera();
        }
        wasPressed = isPressed;
    }
};

Scene::Scene() :
    _cameras()
{
    this->_root = new GameObject(this, "root");
    this->_root->_root = this->_root;

    // Add main camera
    this->_root->addComponent(new Camera());
    // Add scene component
    this->_root->addComponent(new Root());
}

Scene::~Scene()
{
    delete this->_root;
}

void Scene::addLigth(Light *ligth)
{
    this->_ligths.push_back(ligth);
}

Light* Scene::getLigth(std::string id)
{
    Light *ligth = nullptr;

    for (uint32_t i = 0; i < _ligths.size(); ++i) {
        if (_ligths[i]->isLigth(id)) {
            ligth = _ligths[i];
            break;
        }
    }
    return ligth;
}

void Scene::eraseLigth(std::string id)
{
    for (uint32_t i = 0 ; i < _ligths.size(); ++i) {
        if (_ligths[i]->_id == id) {
            delete _ligths[i];
            _ligths.erase(_ligths.begin() + i);
            break;
        }
    }
}

void Scene::changeCamera() {
    this->_camera = (this->_camera + 1) % this->_cameras.size();
}

void Scene::init()
{
    _root->init();
    _root->active();
    _root->getCameras(this->_cameras);
}

void Scene::draw()
{
    Camera *active_camera = this->_cameras[this->_camera];
    std::map<float, std::vector<GameObject*>> transparents;
    std::vector<GameObject*> opaques;

    _root->addLigths(_ligths);
    _root->setCamera(active_camera);
    _root->getQueueDrawGameObjects(transparents, opaques);

    // Step 1: Pintar los objetos opacos...
    for (uint32_t i = 0; i < opaques.size(); ++i) {
        opaques[i]->draw();
    }

    // Step 2: Pintar los objetos ordenados, por transparencia...
    std::map<float, std::vector<GameObject*>>::reverse_iterator it;
    for (it = transparents.rbegin(); it != transparents.rend(); ++it) {
        std::vector<GameObject*> vObjs = it->second;

        for (uint32_t i = 0; i < vObjs.size(); ++i) {
            vObjs[i]->draw();
        }
    }
}

void Scene::update()
{
    _root->update();
}
