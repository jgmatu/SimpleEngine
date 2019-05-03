#ifndef OP_POSITION_H
#define OP_POSITION_H

#include "Movement.hpp"

class Position : public Movement {

public:

    Position(glm::vec3 axis, float angle) :
        _initialModel(1.0)
    {
        _initialModel = glm::rotate(angle, axis);
    };

    Position(glm::vec3 position)
    {
        _initialModel = glm::translate(position);
    }

    ~Position() {
        ;
    }

    void rotate(float angle, glm::vec3 axis) {

    }

    void traslate(glm::vec3 position) {

    }

    glm::mat4 apply() {
        return _initialModel;
    };

    friend std::ostream& operator<<(std::ostream& os, const Position &position) {
        os << "*** Rotate *** " << '\n';
        return os;
    }

private:

    glm::mat4 _initialModel;

};

#endif
