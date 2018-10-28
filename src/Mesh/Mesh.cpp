#include "Mesh/Mesh.hpp"
#include "stb_image.h"

Mesh::Mesh(unsigned id) :
    _vertexPos(),
    _vertexNormal(),
    _vertexTexCoord(),
    _triangleIndex(),
    _NTriangleIndex(0),
    _id(id),
    _VAO(0),
    _textureID(0),
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


void Mesh::loadTexture(const char *filename) {
    std::ifstream file(filename);

    if (file.fail()) {
        throw MeshException("Texture file not exists");
    }
    int width, heigth, channels;
    unsigned char* pixels = stbi_load(filename, &width, &heigth, &channels, 0);

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID); // all upcoming GL_TEXTURE_2D operations now have

    // set the texture wrapping parameters.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    } else if (channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    }
    free(pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Mesh::vertexArrayID() {
    std::cout << "Mesh vertex vertexArrayID" << '\n';
    // Active Vertex Buffer....
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);
}
void Mesh::genVertexBufferPosition() {
    std::cout << "Mesh vertex Buffer genVertexBufferPosition" << '\n';
    // Position attribute...
    glGenBuffers(1, &_VBO);  // Create VertexArrayObject.
    glBindBuffer(GL_ARRAY_BUFFER, _VBO); // Bind Vertex VAO...
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexPos.size() * 3, _vertexPos.data(), GL_STATIC_DRAW); // Assign buffer to VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

}
void Mesh::genVertexBufferNormal() {
    std::cout << "Mesh vertex Buffer genVertexBufferNormal" << '\n';
    // Normal attribute...
    glGenBuffers(1, &_VBO2); // Create VertexArrayObject.
    glBindBuffer(GL_ARRAY_BUFFER, _VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexNormal.size() * 3, _vertexNormal.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);
}
void Mesh::genVertexBufferTextCoord() {
    std::cout << "Mesh vertex Buffer genVertexBufferTextCoord" << '\n';
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
    std::cout << "Draw Mesh!" << '\n';
    // 1st attribute buffer : vertices...

    glActiveTexture(GL_TEXTURE0); // Activate first texture unit... diffuseTexture 0.
    glBindTexture(GL_TEXTURE_2D, _textureID);

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
