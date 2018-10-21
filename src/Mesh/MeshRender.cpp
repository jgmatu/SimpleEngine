#include "Mesh/MeshRender.hpp"

MeshRender::MeshRender() :
    _meshes()
{
    ;
}

MeshRender::~MeshRender() {
    ;
}

void MeshRender::addMesh(Mesh *mesh) {
    _meshes.push_back(mesh);
}

void MeshRender::active() {
    for (unsigned i = 0; i < _meshes.size(); ++i) {
        _meshes[i]->active();
    }
}

void MeshRender::addTexture(const char* filename) {
    for (unsigned i = 0; i < _meshes.size(); ++i) {
        _meshes[i]->loadTexture(filename);
    }
}

void MeshRender::render() {
    for (unsigned i = 0; i < _meshes.size(); ++i) {
        _meshes[i]->draw();
    }
}
