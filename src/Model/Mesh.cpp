#include "Model/Mesh.hpp"

Mesh::Mesh() :
    _id_mesh(""),
    _vertices(),
    _indices(),
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
}

std::string Mesh::getId()
{
    return this->_id_mesh;
}

void Mesh::setMaterial(Material *material)
{
    this->_material = material;
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

    _material->activeTextures();
}

bool Mesh::isTransparent()
{
    return _material->isTransparent();
}

void Mesh::setBlending()
{
    if (_material->isTransparent()) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    } else {
        glDisable(GL_BLEND);
    }
}

void Mesh::draw() {
    // Antes renderizo las texturas definidas de la maya...
    _material->drawTextures();

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

    // Active default texture...
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

std::ostream& operator<<(std::ostream& os, const Mesh& mesh) {
    return os;
}
