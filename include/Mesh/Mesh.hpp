#ifndef MESH_H
#define MESH_H

#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

#include <vector>
#include <iostream>

#include <glad/glad.h>

class Mesh {

public:

    Mesh(unsigned id);
    ~Mesh();

    void active();

    void vertexArrayID();
    void genVertexBufferPosition();
    void genVertexBufferNormal();
    void genVertexBufferTextCoord();
    void genVertexBufferIndex();
    void loadTexture(const char *filename);
    void draw();

    std::vector<float> _vertexPos;
    std::vector<float> _vertexNormal;
    std::vector<float> _vertexTexCoord;
    std::vector<unsigned> _triangleIndex;
    int _NTriangleIndex;

private:

    friend class GameObject;
    unsigned _id;

    // Active Buffer.
    GLuint _VAO;

    GLuint _textureID;

    // Vertices Buffers... // Se puede splitear para meter varias cosas de los vertices
    // en el mismo buffer.
    GLuint _VBO, _VBO2, _VBO3, _EBO;

};

#endif
