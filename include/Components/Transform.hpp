#ifndef TRANSFORM_H
#define TRANSFORM_H

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Components/Component.hpp"
#include "Operations/Operation.hpp"
#include "Operations/Rotate.hpp"
#include "Operations/Scale.hpp"
#include "Operations/Translate.hpp"

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
    void rotate(glm::vec3 vec3, float angle);

    friend std::ostream& operator<<(std::ostream&, const Transform& tf);

    glm::mat4 _gModel, _model;

private:

    std::vector<Operation*> _operations;

};

#endif // TRANSFORM_H
