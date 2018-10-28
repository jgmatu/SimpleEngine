#ifndef OPERATION_H
#define OPERATION_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/ext.hpp>

class Operation {

public:

    virtual ~Operation() {};
    virtual glm::mat4 apply() = 0;

};

#endif
