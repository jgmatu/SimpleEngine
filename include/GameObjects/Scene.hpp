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
    void eraseLigth(LightType type);
    Light* getLigth(std::string id);


    void addChild(GameObject *gameObject) {
        this->_root->addChild(gameObject);
    }

    std::vector<Light*> _ligths;
    std::vector<Camera*> _cameras;

    uint32_t _camera = 0;
    uint32_t _size = 0;

private:

    GameObject *_root;

};

#endif  // SCENE_H
