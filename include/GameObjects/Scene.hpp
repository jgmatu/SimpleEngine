#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <iostream>

#include "GameObjects/GameObject.hpp"
#include "Components/Camera.hpp"

class Scene : public GameObject {

public:

    Scene();
    Scene(unsigned id, std::string name);
    ~Scene();

    const unsigned MAX_CAMERAS = 3;

    std::vector<Camera*> _cameras;
    unsigned _camera = 0;

};

#endif  // SCENE_H
