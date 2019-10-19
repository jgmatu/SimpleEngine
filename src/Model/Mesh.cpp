#include "Model/Mesh.hpp"

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
    _uniforms = new Uniforms();
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

void Mesh::setProgram(Program *program)
{
    this->_program = program;
}

void Mesh::update(Uniforms *uniforms)
{
    this->_uniforms->update(uniforms);
}

void Mesh::setTexture(Texture *texture)
{
    _textures.push_back(texture);
}

void Mesh::activeTextures()
{
    for (uint32_t i = 0; i < _textures.size(); ++i) {
        _textures[i]->activeTexture();
    }
}

void Mesh::active()
{
    // Active this program to visualize this mesh...
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

void Mesh::setBlending()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
}

void Mesh::unsetBlending()
{
    glDisable(GL_BLEND);
}

void Mesh::draw() {
    uint32_t diffuseNr = 0;
    uint32_t specularNr = 0;
    uint32_t normalNr = 0;

    _program->use();
    _program->update(_uniforms);

    for(uint32_t i = 0; i < _textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding

        std::string number;
        std::string name = _textures[i]->_type;
        if(name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        } else if(name == "texture_specular") {
            number = std::to_string(specularNr++);
        } else if (name == "texture_normal") {
            number = std::to_string(normalNr++);
        }
        int value = i;
        _program->setUniform(std::string("material.") + name + number, value);
        glBindTexture(GL_TEXTURE_2D, _textures[i]->_id);
    }
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

    // Active default texture...
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

std::ostream& operator<<(std::ostream& os, const Mesh& mesh) {
    os << "*** DEBUG << MESH!" << mesh._id_mesh;
    return os;
}
