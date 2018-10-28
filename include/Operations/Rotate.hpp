#ifndef OP_ROTATE_H
#define OP_ROTATE_H

#include "Operation.hpp"

class Rotate : public Operation {

public:

    Rotate(float angle, glm::vec3 axis) {
        this->_axis = axis;
        this->_angle = angle;
    };

    Rotate(glm::vec3 axis, glm::quat quat) {
        this->_axis = axis;
        this->_quat = quat;
    };

    ~Rotate() {
        ;
    }

    glm::mat4 apply() {
        return glm::rotate(this->_angle, this->_axis);
    };

private:

    glm::vec3 _axis;
    float _angle;
    glm::quat _quat;

};
#endif
