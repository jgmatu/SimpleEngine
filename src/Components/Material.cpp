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
            _program->createUniform("projection");
            _program->createUniform("view");
            _program->createUniform("model");
            _program->createUniform("diffuseTexture");
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
