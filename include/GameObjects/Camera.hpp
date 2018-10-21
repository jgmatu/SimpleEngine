#ifndef CAMERA_H
#define CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#include "GameObjects/GameObject.hpp"

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

class Camera : public GameObject {

public:

    Camera();
    ~Camera();

    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);

    glm::mat4 _view;
    glm::mat4 _projection;

private:

    float near, far;
    const float aspectRatio = 4.0f / 3.0f;

};

#endif // CAMERA_H
