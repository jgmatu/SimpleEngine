#ifndef OPERATION_H
#define OPERATION_H

#include "Constants/TypeComp.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/ext.hpp>


class Movement {

public:

    virtual ~Movement() {};
    virtual glm::mat4 apply() = 0;

    friend std::ostream& operator<<(std::ostream& os, const Movement &move) {
        os << " *** Move ***" << std::endl;
        return os;
    }
};

#endif
