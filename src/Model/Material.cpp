#include "Model/Material.hpp"

Material::Material() :
    _textures(),
    _transparent(false)
{
    this->_uniforms = new Uniforms();
    this->_program = nullptr;
}

Material::~Material()
{
    std::cout << "Delete component material" << '\n';
}

void Material::setProgram(Program *program)
{
    this->_program = program;
}

size_t Material::sizeTextures()
{
    return this->_textures.size();
}

void Material::setTexture(std::string id_mesh, Texture *texture)
{
    bool isfound = false;
    std::vector<Texture*> textures = this->_textures[id_mesh];

    for (uint32_t i = 0; i < textures.size() && !isfound; ++i) {
        if (textures[i]->_filename.compare(texture->_filename) == 0) {
            isfound = true;
        }
    }
    if (!isfound) {
        std::cout << "add texture : " << texture->_filename << '\n';
        this->_textures[id_mesh].push_back(texture);
    }
}

void Material::update(Light *ligth)
{
    _uniforms->update(ligth->getUniforms());
}

void Material::update(Material *material)
{
    _uniforms->update(material->_uniforms);
}

void Material::setView(Camera *camera)
{
    setParameter("projection", camera->_projection);      // Vertex...
    setParameter("view", camera->_view->_gModel);         // Vertex...
    setParameter("viewPos", camera->viewPos());   // Fragments...
}

void Material::setParameter(std::string name, glm::vec3 val)
{
    _uniforms->setUniformVec3(name, val);
}

void Material::setParameter(std::string name, glm::mat4 val)
{
    _uniforms->setUniformMat4(name, val);
}

void Material::setParameter(std::string name, int val)
{
    _uniforms->setUniformInt(name, val);
}

void Material::setParameter(std::string name, float val)
{
    _uniforms->setUniformFloat(name, val);
}

void Material::setTransparent()
{
    this->_transparent = true;
}

void Material::setOpaque()
{
    this->_transparent = false;
}

bool Material::isTransparent()
{
    return this->_transparent;
}

std::ostream& operator<<(std::ostream& os, const Material& material)
{
    std::map<std::string, std::vector<Texture*>>::const_iterator it_textures;

    for (it_textures = material._textures.begin(); it_textures != material._textures.end(); ++it_textures) {
        std::vector<Texture*> textures = it_textures->second;
        os << "Mesh : " << it_textures->first << "textures : " <<  '\n';
        for (uint32_t i = 0; i < textures.size(); ++i) {
            os << *textures[i] << '\n';
        }
    }
    os << *material._uniforms;
    return os;
}
