#ifndef OP_TRANSLATE_H
#define OP_TRANSLATE_H

#include "Movement.hpp"

class Translate : public Movement {

public:

    Translate(glm::vec3 pos) {
        this->_pos = pos;
    }

    ~Translate() {
        ;
    }

    glm::mat4 apply() {
        return glm::translate(this->_pos);
    }

    friend std::ostream& operator<<(std::ostream& os, const Translate &translate) {
        os << "*** Translate *** " << '\n';
        return os;
    }

private:

    glm::vec3 _pos;

};

#endif
