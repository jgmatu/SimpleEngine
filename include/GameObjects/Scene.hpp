#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <iostream>

#include "GameObjects/GameObject.hpp"
#include "GameObjects/Camera.hpp"

class Scene : public GameObject {

public:

    Scene();
    Scene(unsigned id, std::string name);
    ~Scene();

    Camera* getCamera();

};

#endif  // SCENE_H
