#include "Components/Material.hpp"

Material::Material() :
    _tranparent(false)
{
    this->_type = TypeComp::MATERIAL;
    this->_uniforms = new Uniforms();

    this->_model = nullptr;
    this->_program = nullptr;
}

Material::Material(Model *model, Program *program) :
    Material::Material()
{
    this->_model = model;
    this->_program = program;
}

Material::~Material()
{
    std::cout << "Delete component material" << '\n';
}

void Material::start() {
    if (_model) {
        _model->active();
        if (_program) {
            _program->active();
        }
    }
}

void Material::addLigths(std::vector<Light*> ligths)
{
    for (unsigned i = 0; i < ligths.size(); ++i) {
        ligths[i]->setParameters(_uniforms);
    }
}

void Material::awakeStart() {
    if (_model && _program && _uniforms) {
        _program->render();
        _program->setUniforms(_uniforms);
        _model->render(_program);
        _program->clearUniforms(_uniforms);
    } else {
        throw;
    }
}

void Material::update()
{
    ;
}

void Material::setView(Camera *camera)
{
    this->setParameter("projection", camera->_projection); // Vertex...
    this->setParameter("view", camera->_view->_gModel);      // Vertex...
    this->setParameter("viewPos", -camera->_view->position()); // Fragments...
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
