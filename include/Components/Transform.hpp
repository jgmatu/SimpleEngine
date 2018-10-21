#ifndef TRANSFORM_H
#define TRANSFORM_H

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include "Components/Component.hpp"

class Transform : public Component {

public:

    Transform();
    ~Transform();

    void start();
    void awakeStart();
    void update();

    void scale(glm::vec3 vec3);
    void translate(glm::vec3 vec3);
    void rotate(glm::vec3 vec3, glm::quat quad);

    glm::mat4 model();

    friend std::ostream& operator<<(std::ostream&, const Transform& tf);

private:

    glm::mat4 _gModel, _model;
    glm::vec3 _pos, _scale;
    glm::vec3 _axis;

    glm::quat _quat;
};

#endif // TRANSFORM_H
