#include "Model/Mesh.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Mesh::Mesh() :
    _vertexPos(),
    _vertexNormal(),
    _vertexTexCoord(),
    _index(),
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

Mesh::~Mesh() {
    _vertexPos.clear();
    _vertexNormal.clear();
    _vertexTexCoord.clear();
    _index.clear();
}

void Mesh::loadTextures()
{
    for (unsigned i = 0; i < _textures.size(); ++i) {
        _textures[i].id = TextureFromFile(_textures[i].path, _textures[i].filename.c_str());
    }
}

void Mesh::active2()
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Normal));

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::draw2(Program *program) {
    Uniforms uniforms = Uniforms();

    unsigned diffuseNr = 0;
    unsigned specularNr = 0;

    for(unsigned int i = 0; i < _textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = _textures[i].type;
        if(name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        } else if(name == "texture_specular") {
            number = std::to_string(specularNr++);
        }
        uniforms.setUniformInt("material." + name + number, i);
        glBindTexture(GL_TEXTURE_2D, _textures[i].id);
    }
    program->setUniforms(&uniforms);

    // draw mesh
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexPos.size(), _vertexPos.data(), GL_STATIC_DRAW); // Assign buffer to VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void*) 0);
    glEnableVertexAttribArray(0);

}
void Mesh::genVertexBufferNormal() {
    // Normal attribute...
    glGenBuffers(1, &_VBO2); // Create VertexArrayObject.
    glBindBuffer(GL_ARRAY_BUFFER, _VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexNormal.size(), _vertexNormal.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, (void*) 0);
    glEnableVertexAttribArray(1);
}
void Mesh::genVertexBufferTextCoord() {
    // Text Coord attribute...
    glGenBuffers(1, &_VBO3); // Create VertexArrayObject.
    glBindBuffer(GL_ARRAY_BUFFER, _VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertexTexCoord.size(), _vertexTexCoord.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, (void*) 0);
    glEnableVertexAttribArray(2);
}

void Mesh::genVertexBufferIndex() {
    // Buffer indexes...
    glGenBuffers(1, &_EBO);  // Create VertexArrayObject.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _index.size() * sizeof(GLuint), _index.data(), GL_STATIC_DRAW);
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
        GL_FALSE,           // normalized
        0,                  // stride
        (void*) 0           // array buffer offset
    );
    // Draw the cube!
    glDrawElements(GL_TRIANGLES, _index.size(), GL_UNSIGNED_INT, 0);
}

unsigned Mesh::TextureFromFile(std::string directory, const char *filename) {
    unsigned textureID = 0;
    std::string path = directory + std::string(filename);

    std::ifstream file(path);
    if (file.fail()) {
        std::cerr << "Texture file not exists" << '\n';
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

std::ostream& operator<<(std::ostream& os, const Mesh& mesh) {
    os << "*** DEBUG << MESH!";
    return os;
}
