#include "Components/Material.hpp"

Material::Material() {
    std::cout << "Create component material" << '\n';
}

Material::Material(MeshRender *meshRender, Program *program) {
    std::cout << "Create component material" << '\n';
}

Material::~Material() {
    std::cout << "Delete component material" << '\n';
}

void Material::start() {
    std::cout << "Material start..." << '\n';
}

void Material::awakeStart() {
    std::cout << "Material awakeStart..." << '\n';
}

void Material::update() {
    std::cout << "Material update..." << '\n';
}
