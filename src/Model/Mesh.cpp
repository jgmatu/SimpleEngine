#include "Model/Mesh.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Mesh::Mesh() :
    _id_mesh(""),
    _vertices(),
    _indices(),
    _textures(),
    _VAO(-1),
    _VBO(-1),
    _VBO2(-1),
    _VBO3(-1),
    _EBO(-1)
{
    ;
}

Mesh::Mesh(std::string id_mesh, std::vector<Vertex> vertices, std::vector<unsigned> indices) :
    Mesh::Mesh()
{
    this->_id_mesh = id_mesh;
    this->_vertices = vertices;
    this->_indices = indices;
}

Mesh::~Mesh()
{
    _indices.clear();
    _vertices.clear();
    _textures.clear();
}

std::string Mesh::getId()
{
    return this->_id_mesh;
}

void Mesh::setTexture(__Texture__ *texture)
{
    _textures.push_back(texture);
}

void Mesh::loadTextures()
{
    for (uint32_t i = 0; i < _textures.size(); ++i) {
        _textures[i]->id = TextureFromFile(_textures[i]->path, _textures[i]->filename.c_str());
    }
}

void Mesh::active()
{
    // Active program to visualize this mesh...
    _program->active();

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

    // Vertex positions...
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    // Vertex normals...
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    // Vertex texture coords...
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    // Vertex Tangent...
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Tangent));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

void Mesh::setProgram(Program *program)
{
    this->_program = program;
}

void Mesh::setUniforms(Uniforms *uniforms)
{
    this->_uniforms = uniforms;
}

void Mesh::draw() {
    unsigned diffuseNr = 0;
    unsigned specularNr = 0;
    unsigned normalNr = 0;

    _program->use();
    _program->setUniforms(_uniforms);

    for(uint32_t i = 0; i < _textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding

        std::string number;
        std::string name = _textures[i]->type;
        if(name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        } else if(name == "texture_specular") {
            number = std::to_string(specularNr++);
        } else if (name == "texture_normal") {
            number = std::to_string(normalNr++);
        }
        int value = i;
        _program->setUniform(std::string("material.") + name + number, value);
        glBindTexture(GL_TEXTURE_2D, _textures[i]->id);
    }
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


unsigned Mesh::TextureFromFile(std::string directory, const char *filename) {
    uint32_t textureID = -1;
    std::string path = directory + "/" + std::string(filename);

    std::ifstream file(path);
    if (file.fail()) {
        std::cerr << "Texture file not exists : " << path << '\n';
        throw;
    }
    int32_t width, heigth, channels;
    uint8_t *pixels = stbi_load(path.c_str(), &width, &heigth, &channels, 0);
    if (!pixels) {
        std::cerr << "Error Loading texture on memory..." << '\n';
        stbi_image_free(pixels);
        throw;
    }
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID); // all upcoming GL_TEXTURE_2D.

    // set the texture wrapping parameters.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    } else if (channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return textureID;
}

unsigned Mesh::TextureCubeMap(std::vector<std::string> _faces) {
    unsigned _textureID;
    int width, height, nrChannels;

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);

    for (unsigned int i = 0; i < _faces.size(); ++i) {
        unsigned char *data = stbi_load(_faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (!data) {
            std::cerr << "Cubemap texture failed to load at path: " << _faces[i] << std::endl;
            continue;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,  0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return _textureID;
}

std::ostream& operator<<(std::ostream& os, const Mesh& mesh) {
    os << "*** DEBUG << MESH!" << mesh._id_mesh;
    return os;
}
