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
    std::cout << "**** Material start ****" << '\n';
    if (_meshRender) {
        _meshRender->active();
        if (_program) {
            _program->active();
        }
    }
}

void Material::awakeStart() {
    std::cout << "*** Material awakeStart *** " << '\n';
    if (_meshRender) {
        _meshRender->render();
        if (_program) {
            _program->render();
        }
    }
}

void Material::update() {
    std::cout << "Material update..." << '\n';
}

void Material::createUniform(std::string uniformName) {
    if (_program) {
        _program->createUniform(uniformName);
    }
};
//    void setUniform(std::string name, glm::vec3 value);
//    void setUniform(std::string name, glm::mat4 value);
void Material::setUniform(std::string name, int value) {
    if (_program) {
        _program->setUniform(name, value);
    }
};

void Material::setUniform(std::string name, std::string value) {
    std::cout << "Set uniform -> " << name << " " << value << '\n';
}
