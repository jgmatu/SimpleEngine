
#ifndef CAMERA_H
#define CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#include "Components/Transform.hpp"

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

class Camera : public Component {

public:

    Camera();
    ~Camera();

    // Este método SOLO se llama una vez la primera vez que se crea el componente.
    void start();

    // Método que se llama cada vez que el Componente se activa.
    void awakeStart();

    // Método que realiza transformaciones, cálculos de cosas.
    void update(Clock *clock);

    // position vector is inverted since we eventually want to translate
    // the world in the opposite direction of where we want to move.
    glm::vec3 position();

    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);

    Transform *_view;
    glm::mat4 _projection;

private:
    friend class GameObject;

    // Trackers cameras...
    Transform *_tfObj;

    float near, far;
    const float aspectRatio = 4.0f / 3.0f;
};

#endif // CAMERA_H
