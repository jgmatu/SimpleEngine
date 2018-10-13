#ifndef CAMERA_H
#define CAMERA_H


#include "GameObjects/GameObject.hpp"

#include <iostream>
#include <string>


class Camera : public GameObject {

public:

    Camera();
    ~Camera();

private:

    std::string _view;
    std::string _projection;

    float near, far;

    const float aspectRatio = 4.0f / 3.0f;

};

#endif // CAMERA_H
