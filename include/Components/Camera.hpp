#ifndef CAMERA_H
#define CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#include "GameObjects/GameObject.hpp"

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

class Camera : public Component {

public:

    Camera(GameObject *gameObject);
    ~Camera();

    // Este método SOLO se llama una vez la primera vez que se crea el componente.
    void start();

    // Método que se llama cada vez que el Componente se activa.
    void awakeStart();

    // Método que realiza transformaciones, cálculos de cosas.
    void update();

    void setGameObject(GameObject *gameObject) {
        this->_gameObject = gameObject;
    };

    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);

    Transform *_tf;
    glm::mat4 _projection;

private:

    GameObject *_gameObject;

    float near, far;
    const float aspectRatio = 4.0f / 3.0f;
};

#endif // CAMERA_H
