#ifndef MESH_H
#define MESH_H

#include <vector>
#include <iostream>

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
    unsigned _VAO;

    // Vertices Buffers... // Se puede splitear para meter varias cosas de los vertices
    // en el mismo buffer.
    unsigned _VBO, _VBO2, _VBO3, _EBO;

};

#endif
