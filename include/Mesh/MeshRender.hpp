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

    void active();
    void render();
    void addMesh(Mesh *mesh);
    void addTexture(const char* filename);

    friend std::ostream& operator<<(std::ostream& os, const MeshRender& meshRender);

private:

    friend class GameObject;
    std::vector<Mesh*> _meshes;

};

#endif
