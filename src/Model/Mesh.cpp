#include "Model/Mesh.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Mesh::Mesh() :
    _vertices(),
    _indices(),
    _textures(),
    _VAO(0),
    _VBO(0),
    _VBO2(0),
    _VBO3(0),
    _EBO(0)
{
    ;
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<__Texture__> textures) :
    Mesh::Mesh()
{
    this->_vertices = vertices;
    this->_indices = indices;
    this->_textures = textures;
}

Mesh::~Mesh()
{
    _indices.clear();
    _vertices.clear();
    _textures.clear();
}

void Mesh::loadTextures()
{
    for (unsigned i = 0; i < _textures.size(); ++i) {
        _textures[i].id = TextureFromFile(_textures[i].path, _textures[i].filename.c_str());
    }
}

void Mesh::active()
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

    // Vertex positions...
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);

    // Vertex normals...
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Normal));

    // Vertex texture coords...
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::draw(Program *program) {
    unsigned diffuseNr = 0;
    unsigned specularNr = 0;

    for(unsigned i = 0; i < _textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding

        // Retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = _textures[i].type;
        if(name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        } else if(name == "texture_specular") {
            number = std::to_string(specularNr++);
        }
        int value = i;
        program->setUniform("material." + name + number, value);
        glBindTexture(GL_TEXTURE_2D, _textures[i].id);
    }

    // Draw mesh
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Always good practice to set everything back to defaults once configured...
    glActiveTexture(GL_TEXTURE0);
}


unsigned Mesh::TextureFromFile(std::string directory, const char *filename) {
    unsigned textureID = 0;
    std::string path = directory + "/" + std::string(filename);

    std::ifstream file(path);
    if (file.fail()) {
        std::cerr << "Texture file not exists : " << directory << "/" << filename  << '\n';
        throw;
    }
    int width, heigth, channels;
    unsigned char* pixels = stbi_load(path.c_str(), &width, &heigth, &channels, 0);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID); // all upcoming GL_TEXTURE_2D operations now have

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
            std::cout << "Cubemap texture failed to load at path: " << _faces[i] << std::endl;
            continue;
        }
        std::cout << "Success loaded texture cubemap : " << _faces[i] << " Width : " << width << " Height : " << height << " Channels : " << nrChannels << '\n';
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
    os << "*** DEBUG << MESH!";
    return os;
}
