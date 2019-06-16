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
    Scene(unsigned id, std::string name);
    ~Scene();

    void init();
    void draw();
    void update(Keyboard *keyboard, Clock *clock);

    void setLigth(Light *ligth);
    void eraseLigth(CompLigth type);

    void addChild(GameObject *gameObject)
    {
        this->_root->addChild(gameObject);
    }

    std::vector<Light*> _ligths;
    std::vector<Camera*> _cameras;

    uint32_t _camera = 0;
    uint32_t _size = 0;

private:

    GameObject *_root;

    std::vector<Light*> getLigthPoints();
    void addDefaultLigths();

};

#endif  // SCENE_H
