#include "GameObjects/Scene.hpp"

Scene::Scene() :
    _cameras()
{
    this->_root = new GameObject("root");
    this->_root->_root = this->_root;

    Camera *main_camera = new Camera();
    this->_root->addComponent(main_camera);
}

Scene::~Scene()
{
    delete this->_root;
}

void Scene::setLigth(Light *ligth)
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

void Scene::eraseLigth(CompLigth component)
{
    bool erase = false;

    for (uint32_t i = 0 ; i < _ligths.size() && !erase; ++i) {
        if (_ligths[i]->_type == component) {
            delete _ligths[i];
            _ligths.erase (_ligths.begin() + i);
            erase = true;
        }
    }
}
void Scene::init()
{
    _root->init();
    _root->getCameras(this->_cameras);
}

void Scene::draw()
{
    Camera *active_camera = this->_cameras[this->_camera];
    std::map<float, std::vector<GameObject*>> transparents;

    _root->addLigths(_ligths);
    _root->draw(active_camera, transparents);

    // Pintar los objetos ordenados, por transparencia...
    std::map<float, std::vector<GameObject*>>::reverse_iterator it;
    for(it = transparents.rbegin(); it != transparents.rend(); ++it) {
        std::vector<GameObject*> vObjs = it->second;

        for (uint32_t i = 0; i < vObjs.size(); ++i) {
            vObjs[i]->draw(active_camera);
        }
    }
}

void Scene::update()
{
    _root->update();
}
