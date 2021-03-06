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

class Transform : public Component {

public:

    Transform();
    ~Transform();

    void start();
    void update();

    void addChild(Transform *tf);
    glm::vec3 position() const;

    friend std::ostream& operator<<(std::ostream&, const Transform& tf);

    glm::mat4 _gModel, _model, _last_model, _inital_position;

private:

    bool isMove(glm::mat4 _model, glm::mat4 last_model);

    std::vector<Transform*> tfChilds;

};

#endif // TRANSFORM_H
