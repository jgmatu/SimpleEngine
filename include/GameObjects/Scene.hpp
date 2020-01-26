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

    void eraseLigth(std::string id);
    Light* getLigth(std::string id);


    void addChild(GameObject *gameObject) {
        this->_root->addChild(gameObject);
    }

    void addLigths(const std::vector<Light*>& ilumination) {
        _ligths = ilumination;
    }

    std::vector<Light*> _ligths;
    std::vector<Camera*> _cameras;

    uint32_t _camera = 0;
    uint32_t _size = 0;

private:

    GameObject *_root;

};

#endif  // SCENE_H
