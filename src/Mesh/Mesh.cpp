#include "Mesh/Mesh.hpp"

Mesh::Mesh(unsigned id) :
    _vertexPos(),
    _vertexNormal(),
    _vertexTexCoord(),
    _triangleIndex(),
    _NTriangleIndex(0),
    _VAO(0),
    _VBO(0),
    _VBO2(0),
    _VBO3(0),
    _EBO(0),
    _id(id)
{
    ;
}

Mesh::~Mesh() {
    _vertexPos.clear();
    _vertexNormal.clear();
    _vertexTexCoord.clear();
    _triangleIndex.clear();
}

void Mesh::active() {
    vertexArrayID();
    genVertexBufferPosition();
    genVertexBufferNormal();
    genVertexBufferTextCoord();
    genVertexBufferIndex();
}

void Mesh::draw() {
    std::cout << "draw Mesh!" << '\n';
}

void Mesh::vertexArrayID() {
    std::cout << "Mesh vertex vertexArrayID" << '\n';
}
void Mesh::genVertexBufferPosition() {
    std::cout << "Mesh vertex Buffer genVertexBufferPosition" << '\n';
}
void Mesh::genVertexBufferNormal() {
    std::cout << "Mesh vertex Buffer genVertexBufferNormal" << '\n';
}
void Mesh::genVertexBufferTextCoord() {
    std::cout << "Mesh vertex Buffer genVertexBufferTextCoord" << '\n';
}

void Mesh::genVertexBufferIndex() {
    std::cout << "Mesh vertex Buffer genVertexBufferIndex" << '\n';
}
