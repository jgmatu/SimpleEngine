#include "Components/Material.hpp"

Material::Material() :
    _tranparent(false)
{
    this->_type = TypeComp::MATERIAL;
    this->_uniforms = new Uniforms();

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

void Material::start() {
    if (_model) {
        _model->active();
        if (_program) {
            _program->active();
        }
    }
}

void Material::awakeStart() {
    if (_model && _program && _uniforms) {

        for (unsigned i = 0; i < _ligths.size(); ++i) {
            _ligths[i]->setParameters(_uniforms);
        }

        _program->setUniforms(_uniforms);

        _model->render(_program);
        _program->render();

        _program->clearUniforms(_uniforms);
    } else {
        throw;
    }
}

void Material::update()
{
    ;
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

void Material::setLigth(Light *ligth)
{
    this->_ligths.push_back(ligth);
}

void Material::eraseLigth(CompLigth component)
{
    bool erase = false;

    for (unsigned i = 0 ; i < _ligths.size() && !erase; ++i) {
        if (_ligths[i]->_type == component) {
            delete _ligths[i];
            _ligths.erase (_ligths.begin() + i);
            erase = true;
        }
    }
}

void Material::setProgram(Program *program) {
    _program = program;
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
