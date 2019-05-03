#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <iostream>

#include "GameObjects/GameObject.hpp"

#include "Components/Camera.hpp"
#include "Components/Light.hpp"

class Scene {

public:

    Scene();
    Scene(unsigned id, std::string name);
    ~Scene();

    void init();
    void draw();
    void update();

    void initCameras();

    void setCamera(Camera *camera);
    void eraseCamera(int idx);

    void setLigth(Light *ligth);
    void eraseLigth(CompLigth type);

    void addGameObjects(std::vector<GameObject*> objects) {
        for (unsigned i = 0; i < objects.size(); ++i) {
            Component *component = objects[i]->getComponent(TypeComp::CAMERA);
            if (Camera *camera = dynamic_cast<Camera*>(component)) {
                this->_cameras.push_back(camera);
            }
        }
        this->_root->addGameObjects(objects);
    }

    std::vector<Light*> _ligths;
    std::vector<Camera*> _cameras;
    unsigned _camera = 0;
    unsigned _size = 0;

private:

    GameObject *_root;

    Camera* updateCameras();
    std::vector<Light*> getLigthPoints();
    void addDefaultLigths();

};

#endif  // SCENE_H
