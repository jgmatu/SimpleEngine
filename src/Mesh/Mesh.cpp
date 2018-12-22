#include "Mesh/Mesh.hpp"

Mesh::Mesh(unsigned id, std::string name) :
    _vertexPos(),
    _vertexNormal(),
    _vertexTexCoord(),
    _triangleIndex(),
    _NTriangleIndex(0),
    _id(id),
    _name(name),
    _VAO(0),
    _VBO(0),
    _VBO2(0),
    _VBO3(0),
    _EBO(0)
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

void Mesh::vertexArrayID() {
    // Active Vertex Buffer....
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);
}

void Mesh::genVertexBufferPosition() {
    // Position attribute...
    glGenBuffers(1, &_VBO);  // Create VertexArrayObject.
    glBindBuffer(GL_ARRAY_BUFFER, _VBO); // Bind Vertex VAO...
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexPos.size() * 3, _vertexPos.data(), GL_STATIC_DRAW); // Assign buffer to VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

}
void Mesh::genVertexBufferNormal() {
    // Normal attribute...
    glGenBuffers(1, &_VBO2); // Create VertexArrayObject.
    glBindBuffer(GL_ARRAY_BUFFER, _VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexNormal.size() * 3, _vertexNormal.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);
}
void Mesh::genVertexBufferTextCoord() {
    // Text Coord attribute...
    glGenBuffers(1, &_VBO3); // Create VertexArrayObject.
    glBindBuffer(GL_ARRAY_BUFFER, _VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexTexCoord.size() * 2, _vertexTexCoord.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(2);
}

void Mesh::genVertexBufferIndex() {
    // Buffer indexes...
    glGenBuffers(1, &_EBO);  // Create VertexArrayObject.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _triangleIndex.size() * sizeof(GLuint), _triangleIndex.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the VBO.
    glBindVertexArray(0); // Unbind the VAO.
}

void Mesh::draw() {
    glBindVertexArray(_VAO); // Activa la geometría que se va a pintar.
    glBindBuffer(GL_ARRAY_BUFFER, _VBO); // Activar el buffer de vertices a pintar.
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*) 0           // array buffer offset
    );
    // Draw the cube!
    glDrawElements(GL_TRIANGLES, _NTriangleIndex, GL_UNSIGNED_INT, 0);
}

std::ostream& operator<<(std::ostream& os, const Mesh& mesh) {
    os << mesh._name;
    return os;
}
