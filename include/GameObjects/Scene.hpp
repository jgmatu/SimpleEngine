#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <iostream>

#include "GameObjects/GameObject.hpp"
#include "Components/Camera.hpp"
#include "Ligths/Light.hpp"

class Scene {

public:

    Scene();
    ~Scene();

    void init();
    void draw();
    void update();

    void addLigth(Light *ligth);
    Light* getLigth(std::string id);

    void addChild(GameObject *gameObject) {
        this->_root->addChild(gameObject);
    }

    void addLigths(const std::vector<Light*>& ilumination) {
        _ligths = ilumination;
    }

    void changeCamera();

private:

    void eraseLigth(std::string id);

    uint32_t _camera = 0;
    GameObject *_root;

    std::vector<Light*> _ligths;
    std::vector<Camera*> _cameras;
};

#endif  // SCENE_H
