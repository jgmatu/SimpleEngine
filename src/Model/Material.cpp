#include "Model/Material.hpp"

Material::Material() :
    _textures(),
    _transparent(false)
{
    this->_uniforms = new Uniforms();
}

Material::~Material()
{
    std::cout << "Delete component material" << '\n';
}

size_t Material::sizeTextures()
{
    return this->_textures.size();
}

void Material::addNewTexture(Texture *texture)
{
    std::string number;
    std::string name = texture->_type; 

    if (name == "texture_diffuse") {
        number = std::to_string(this->_diffuseNr++);
    } else if(name == "texture_specular") {
        number = std::to_string(this->_specularNr++);
    } else if (name == "texture_normal") {
        number = std::to_string(this->_normalNr++);
    }
    this->_uniforms->setUniformInt(std::string("material.") + name + number, this->_nTexture++);
    this->_textures.push_back(texture);
}

void Material::setTexture(std::string id_mesh, Texture *texture)
{
    bool isfound = false;

    for (uint32_t i = 0; i < this->_textures.size() && !isfound; ++i) {
        isfound = this->_textures[i]->_filename.compare(texture->_filename) == 0;
    }
    if (!isfound) {
        addNewTexture(texture);
    }
}

void Material::setTransparent()
{
    this->_transparent = true;
}

void Material::setOpaque()
{
    this->_transparent = false;
}

bool Material::isTransparent() const
{
    return this->_transparent;
}

void Material::activeTextures()
{
    for (uint32_t i = 0; i < _textures.size(); ++i) {
        _textures[i]->activeTexture();
    }
}

void Material::drawTextures()
{
    for (uint32_t i = 0; i < _nTexture; ++i) {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        glBindTexture(GL_TEXTURE_2D, _textures[i]->_id);
    }
}

std::ostream& operator<<(std::ostream& os, const Material& material)
{
    for (uint32_t i = 0; i < material._textures.size(); ++i) {
        os << *material._textures[i] << '\n';
    }
    os << *material._uniforms;
    return os;
}
