#ifndef OP_SCALE_H
#define OP_SCALE_H

#include "Movement.hpp"

class Scale : public Movement {

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

    friend std::ostream& operator<<(std::ostream& os, const Scale &scale) {
        os << "*** Scale *** " << '\n';
        return os;
    }

private:

    glm::vec3 _scale;
};

#endif
