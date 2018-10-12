#ifndef MESH_RENDER_H
#define MESH_RENDER_H

#include <vector>
#include <iostream>
#include <string>

#include "Mesh/Mesh.hpp"

class MeshRender {

public:

    MeshRender();
    ~MeshRender();

private:

    std::vector<Mesh*> _meshes;

};

#endif
