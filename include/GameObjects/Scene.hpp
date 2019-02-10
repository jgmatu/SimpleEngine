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

    void setCamera(Camera *camera);
    void eraseCamera(int idx);

    void setLigth(Light *ligth);
    void eraseLigth(CompLigth type);

    void addGameObjects(std::vector<GameObject*> objects) {
        this->_root->addGameObjects(objects);
    }

    const unsigned MAX_CAMERAS = 3;

    std::vector<Light*> _ligths;
    std::vector<Camera*> _cameras;
    unsigned _camera = 0;

private:

    GameObject *_root;

    Camera* updateCameras();
    std::vector<Light*> getLigthPoints();
    void addDefaultLigths();

};

#endif  // SCENE_H
