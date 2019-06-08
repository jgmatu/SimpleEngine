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

#include "Program/Program.hpp"

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

struct __Texture__ {
    unsigned id;
    std::string type;
    std::string filename;
    std::string path;
};

class Mesh {

public:

    Mesh(std::string id_mesh, std::vector<Vertex> vertices, std::vector<unsigned> indices);

    Mesh();
    ~Mesh();

    std::string getId();

    void active();
    void draw();
    void loadTextures();

    void setTexture(__Texture__ *texture);
    void setProgram(Program *program);
    void setUniforms(Uniforms *uniforms);

    friend std::ostream& operator<<(std::ostream& os, const Mesh& mesh);

    static unsigned TextureFromFile(std::string directory, const char *filename);
    static unsigned TextureCubeMap(std::vector<std::string> _faces);

private:

    void vertexArrayID();
    void genVertexBufferPosition();
    void genVertexBufferNormal();
    void genVertexBufferTextCoord();
    void genVertexBufferIndex();

    std::string _id_mesh;

    // Vertex data...
    std::vector<Vertex> _vertices;
    std::vector<unsigned> _indices;

    //Textures mesh...
    std::vector<__Texture__*> _textures;

    // Active Buffer.
    GLuint _VAO;

    // Vertices Buffers... // Se puede splitear para meter varias cosas de los vertices
    // en el mismo buffer.
    GLuint _VBO, _VBO2, _VBO3, _EBO;

    Program *_program;
    Uniforms *_uniforms;

};

#endif
