#ifndef PLANE_H
#define PLANE_H

#include "Geometries/Geometry.hpp"

class Plane : public Geometry {

public:

    Plane(std::string id_mesh);
    ~Plane();

    Mesh* getMesh();

private:

    void generatePlaneMesh(std::string id_mesh);
};

#endif
