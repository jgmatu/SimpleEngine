#ifndef SPHERE_H
#define SPHERE_H

#include <Geometries/Geometry.hpp>

class Sphere : public Geometry {

public:

    Sphere(std::string id_mesh);

    Mesh* getMesh();

private:

    void generateSphereMesh(std::string id_mesh);

};


#endif
