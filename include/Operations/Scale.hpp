#ifndef OP_SCALE_H
#define OP_SCALE_H

#include "Operation.hpp"

class Scale : public Operation {

public:

    Scale(glm::vec3 scale) {
        this->_scale = scale;
    }

    ~Scale() {
        ;
    }

    glm::mat4 apply() {
        return glm::scale(this->_scale);
    }

private:

    glm::vec3 _scale;
};

#endif
