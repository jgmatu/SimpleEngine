#ifndef CUBE_H
#define CUBE_H

#include "Geometries/Geometry.hpp"

class Cube : public Geometry {

public:

    Cube(std::string id_mesh);
    ~Cube();

    Mesh* getMesh();

private:

    void generateCubeMesh(std::string id_mesh);

};

#endif
