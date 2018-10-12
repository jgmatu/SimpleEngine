#ifndef CAMERA_H
#define CAMERA_H

#include "Components/Component.hpp"

#include <iostream>
#include <string>


class Camera : public Component {

public:

    Camera();
    ~Camera();

    void start();
    void awakeStart();
    void update();

private:

    std::string _view;
    std::string _projection;

    float near, far;

    const float aspectRatio = 4.0f / 3.0f;

};

#endif // CAMERA_H
