#ifndef OP_TRANSLATE_H
#define OP_TRANSLATE_H

#include "Operation.hpp"

class Translate : public Operation {

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

private:

    glm::vec3 _pos;

};

#endif
