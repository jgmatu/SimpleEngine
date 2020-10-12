#ifndef MESH_H
#define MESH_H

#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES

#include <vector>
#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Model/Material.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include <glad/glad.h>

class MeshException : public std::exception {

public:
    MeshException(const std::string& msg) :
        _msg(msg)
    {
        ;
    }
    virtual const char* what () const throw () {
        char *msg = (char *) malloc(sizeof(char) * 1024);

        if (!msg) {
            fprintf(stderr, "Mesh malloc error : %s\n", strerror(errno));
            return "";
        }
        sprintf(msg, "Mesh error : %s\n", _msg.c_str());
        return msg;
    }

private:
    std::string _msg;
};

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
};

class Mesh {

public:

    Mesh(std::string id_mesh, std::vector<Vertex> vertices, std::vector<uint32_t> indices);

    Mesh();
    ~Mesh();

    std::string getId();

    void active();
    void draw();
    void setBlending(bool isTransparent);

    void setMaterial(Material *material);

    friend class Model;
    friend std::ostream& operator<<(std::ostream& os, const Mesh& mesh);

private:
    // OpenGL Interface internal processing.

    void vertexArrayID();
    void genVertexBufferPosition();
    void genVertexBufferNormal();
    void genVertexBufferTextCoord();
    void genVertexBufferIndex();

    std::string _id_mesh;

    // Vertex data...
    std::vector<Vertex> _vertices;
    std::vector<GLuint> _indices;

    // Active Buffer.
    GLuint _VAO;

    // Vertices Buffers...
    // Se puede splitear para meter varios atributos de los vertices en el
    // mismo buffer.
    GLuint _VBO, _VBO2, _VBO3, _EBO;

    Material *_material;
};

#endif
