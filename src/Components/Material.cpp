#include "Components/Material.hpp"

Material::Material() {
    this->_type = TypeComp::MATERIAL;
    std::cout << "Create component material" << '\n';
}

Material::Material(MeshRender *meshRender, Program *program) :
    Material::Material()
{
    this->_meshRender = meshRender;
    this->_program = program;
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
        }
    }
}

void Material::awakeStart() {
    if (_meshRender) {
        _meshRender->render();
        if (_program) {
            _program->render();
        }
    }
}

void Material::update() {
    if (_meshRender) {
        _meshRender->render();
        if (_program) {
            _program->render();
        }
    }
}

void Material::createUniform(std::string uniformName) {
    if (_program) {
        _program->createUniform(uniformName);
    }
};

void Material::setUniform(std::string name, glm::vec3 value) {
    if (_program) {
        _program->setUniform(name, value);
    }
}

void Material::setUniform(std::string name, glm::mat4 value) {
    if (_program) {
        _program->setUniform(name, value);
    }
}

void Material::setUniform(std::string name, int value) {
    if (_program) {
        _program->setUniform(name, value);
    }
}

void Material::addTexture(const char *filename) {
    if (_meshRender) {
        _meshRender->addTexture(filename);
    }
}

std::ostream& operator<<(std::ostream& os, const Material& material) {
    os << *material._meshRender;
    return os;
}
