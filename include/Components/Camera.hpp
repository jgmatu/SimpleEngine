
#ifndef CAMERA_H
#define CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include "Components/Component.hpp"
#include "Components/Transform.hpp"

class Camera : public Component {

public:

    Camera();
    ~Camera();

    void start();
    void update();

    void translate(glm::vec3 vec3);
    void rotate(glm::vec3 vec3, float angle);

    Transform *_view;
    glm::mat4 _projection;

    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);

private:
    friend class GameObject;
    friend class Render;

    // position vector is inverted since we eventually want to translate
    // the world in the opposite direction of where we want to move.
    glm::vec3 viewPos();

    // Trackers cameras...
    Transform *_tfObj;

    float near, far;
    const float aspectRatio = 4.0f / 3.0f;
};

#endif // CAMERA_H
