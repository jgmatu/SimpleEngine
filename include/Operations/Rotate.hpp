#ifndef OP_ROTATE_H
#define OP_ROTATE_H

#include "Movement.hpp"

class Rotate : public Movement {

public:

    Rotate(float delta_angle, glm::vec3 axis) {
        this->_axis = axis;
        this->_delta_angle = delta_angle;
        this->_angle = 0.0f;
    };

    Rotate(glm::vec3 axis, glm::quat quat) {
        this->_axis = axis;
        this->_quat = quat;
    };

    ~Rotate() {
        ;
    }

    glm::mat4 apply() {
        // Aplicar el movimiento angular con un incremento del angulo
        // de manera circular...
        this->_angle += this->_delta_angle * (MOVEMENT_TIME / 1000.0f);
//        std::cout << "Delta angle : " << this->_angle << '\n';
        return glm::rotate(this->_angle, this->_axis);
    };

    friend std::ostream& operator<<(std::ostream& os, const Rotate &rotate) {
        os << "*** Rotate *** " << '\n';
        return os;
    }

private:

    glm::vec3 _axis;
    float _delta_angle;
    float _angle;
    glm::quat _quat;

};
#endif
