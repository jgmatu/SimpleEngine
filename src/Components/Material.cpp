#include "Components/Material.hpp"

Material::Material() {
    this->_type = TypeComp::MATERIAL;
    std::cout << "Create component material" << '\n';
}

Material::Material(MeshRender *meshRender, Program *program, Uniforms *uniforms) :
    Material::Material()
{
    this->_meshRender = meshRender;
    this->_program = program;
    this->_uniforms = uniforms;
    std::cout << "Create component material" << '\n';
}

Material::~Material() {
    std::cout << "Delete component material" << '\n';
}

void Material::start() {
    if (_meshRender) {
        _meshRender->active();
        if (_program) {
            _program->active();
            std::cout << " *** Trace material.., *** " << '\n';
        }
    }
}

void Material::awakeStart() {
    if (_program) {
        _program->setUniforms(_uniforms);
    }
    if (_meshRender) {
        _meshRender->render();
        if (_program) {
            _program->render();
        }
    }
}

void Material::update() {
    if (_program) {
        _program->setUniforms(_uniforms);
    }
    if (_meshRender) {
        _meshRender->render();
        if (_program) {
            _program->render();
        }
    }
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

std::ostream& operator<<(std::ostream& os, const Material& material) {
    os << *material._meshRender;
    return os;
}
