#ifndef OP_ROTATE_H
#define OP_ROTATE_H

#include "Movement.hpp"

class Rotate : public Movement {

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

    friend std::ostream& operator<<(std::ostream& os, const Rotate &rotate) {
        os << "*** Rotate *** " << '\n';
        return os;
    }

private:

    glm::vec3 _axis;
    float _angle;
    glm::quat _quat;

};
#endif
