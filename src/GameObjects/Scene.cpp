#include "GameObjects/Scene.hpp"

Scene::Scene() :
    _cameras()
{
    this->_root = new GameObject();

    Camera *main_camera = new Camera();
    this->_root->addComponent(main_camera);
    this->_cameras.push_back(main_camera);

    this->addDefaultLigths();
//    std::cout << "Create GameObject Scene" << '\n';
}

Scene::Scene(unsigned id, std::string name) :
    Scene()
{
//    std::cout << "Create GameObject Scene" << '\n';
}

Scene::~Scene() {
    for (unsigned i = 0; i < 3; ++i) {
        delete this->_cameras[i];
    }
}

std::vector<Light*> Scene::getLigthPoints()
{
    std::vector<glm::vec3> point_positions = {
        glm::vec3( 2.0,  2.0, -1.0),
        glm::vec3(-2.0,  1.0,  1.0),
        glm::vec3(-1.0,  2.0,  3.0),
        glm::vec3( 0.0, -2.0,  0.0)
    };

    std::vector<Light*> points;
    for (unsigned i = 0; i < point_positions.size(); ++i) {
        points.push_back(new Point(i, point_positions[i]));
    }
    return points;
}

void Scene::addDefaultLigths()
{
    std::vector<Light*> points = getLigthPoints();

    for (unsigned i = 0; i < points.size(); ++i) {
        this->setLigth(points[i]);
    }
    this->setLigth(new Specular(glm::vec3(0.7, 0.7, 0.7), 0.078125));
    this->setLigth(new Spot(glm::vec3(1.0f, 1.0f, -2.0f), glm::vec3(0.0f, 0.0f, 1.0), 2.5, 7.5));
    this->setLigth(new Directional(glm::vec3(0.0, 0.0, 0.0)));
}

void Scene::setLigth(Light *ligth)
{
    this->_ligths.push_back(ligth);
}

void Scene::eraseLigth(CompLigth component)
{
    bool erase = false;

    for (unsigned i = 0 ; i < _ligths.size() && !erase; ++i) {
        if (_ligths[i]->_type == component) {
            delete _ligths[i];
            _ligths.erase (_ligths.begin() + i);
            erase = true;
        }
    }
}
void Scene::init() {
    _root->init();
}

Camera* Scene::updateCameras()
{
    for (unsigned i = 0; i < this->_cameras.size(); ++i) {
        this->_cameras[i]->update();
    }
    return this->_cameras[this->_camera];
}

void Scene::draw() {
    Camera *active_camera = this->updateCameras();
    std::map<float, std::vector<GameObject*>> sorted;

    _root->addLigths(_ligths);
    _root->draw(active_camera, sorted);

    // Pintar los objetos ordenados, por transparencia...
    for(std::map<float, std::vector<GameObject*>>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it) {
        std::vector<GameObject*> vObjs = it->second;

        for (unsigned i = 0; i < vObjs.size(); ++i) {
            vObjs[i]->draw(active_camera);
        }
    }
//    std::cout << "Active Camera : " << *active_camera << '\n';
}


void Scene::update() {
    _root->update();
}
