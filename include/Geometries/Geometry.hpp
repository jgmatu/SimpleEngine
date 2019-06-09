#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glad/glad.h>

#include <string>
#include <vector>
#include <string>

#include <Model/Mesh.hpp>

class Geometry {

public:

    virtual ~Geometry() {};
    Mesh* getMesh() { return this->_mesh; };

protected:

    Mesh *_mesh;
};

#endif
