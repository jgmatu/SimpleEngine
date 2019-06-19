#include "Components/Material.hpp"

Material::Material() :
    _tranparent(false)
{
    this->_type = TypeComp::MATERIAL;
    this->_uniforms = new Uniforms();

    this->_model = nullptr;
    this->_program = nullptr;
}

Material::Material(Model *model) :
    Material::Material()
{
    this->_model = model;
}

Material::~Material()
{
    std::cout << "Delete component material" << '\n';
}

void Material::setProgram(Program *program)
{
    this->_program = program;
}

void Material::setTexture(std::string id_mesh, Texture *texture)
{
    std::vector<Texture*> textures = this->_textures[id_mesh];
    bool isfound = false;
    for (uint32_t i = 0; i < textures.size() && !isfound; ++i) {
        if (textures[i]->_filename.compare(texture->_filename) == 0) {
            isfound = true;
        }
    }
    if (!isfound) {
        this->_textures[id_mesh].push_back(texture);
    }
}

void Material::start() {
    if (_model) {
        if (_program) {
            _model->setProgram(_program);
        }
        if (_textures.size() == 0) {
            std::cout << "Material: Not textures atached" << '\n';
        }
        _model->setTextures(_textures);
        _model->active();
    }
}

void Material::addLigths(std::vector<Light*> ligths)
{
    for (unsigned i = 0; i < ligths.size(); ++i) {
        ligths[i]->setParameters(_uniforms);
    }
}

void Material::awakeStart() {
    if (_model) {
        _model->setUniforms(_uniforms);
        _model->draw();
    }
}

void Material::update(Clock *clock)
{
//    std::cout << "update material.." << '\n';
}

void Material::setView(Camera *camera)
{
    this->setParameter("projection", camera->_projection);      // Vertex...
    this->setParameter("view", camera->_view->_gModel);         // Vertex...
    this->setParameter("viewPos", camera->position());   // Fragments...
}

void Material::setParameter(std::string name, glm::vec3 val) {
    _uniforms->setUniformVec3(name, val);
}

void Material::setParameter(std::string name, glm::mat4 val) {
    _uniforms->setUniformMat4(name, val);
}

void Material::setParameter(std::string name, int val) {
    _uniforms->setUniformInt(name, val);
}

void Material::setParameter(std::string name, float val) {
    _uniforms->setUniformFloat(name, val);
}

void Material::setTransparent()
{
    this->_tranparent = true;
}

void Material::setOpaque()
{
    this->_tranparent = false;
}

bool Material::isTransparent()
{
    return this->_tranparent;
}

std::ostream& operator<<(std::ostream& os, const Material& material) {
    os << *material._model;
    return os;
}
