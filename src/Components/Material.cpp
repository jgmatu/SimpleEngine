#include "Components/Material.hpp"

Material::Material() {
    this->_type = TypeComp::MATERIAL;
    this->_uniforms = new Uniforms();
    this->_textures = new Textures();

    this->_program = nullptr;
}

Material::Material(MeshRender *meshRender) :
    Material::Material()
{
    this->_meshRender = meshRender;
}

Material::~Material()
{
    std::cout << "Delete component material" << '\n';
}

void Material::start() {
    if (_meshRender) {
        _meshRender->active();
        if (_program) {
            _program->active();
        }
        if (_textures) {
            _textures->active();
        }
    }
}

void Material::awakeStart() {
    for (unsigned i = 0; i < _ligths.size(); ++i) {
        _ligths[i]->setParameters(_uniforms);
    }
    if (_textures) {
        _textures->setParameters(_uniforms);
    }

    if (_program) {
        _program->setUniforms(_uniforms);
    }

    if (_textures) {
        _textures->render();
    }

    if (_meshRender) {
        _meshRender->render();
        if (_program) {
            _program->render();
        }
    }

    if (_program) {
        _program->clearUniforms(_uniforms);
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

void Material::setTexture(Texture *texture) {
    _textures->setTexture(texture);
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

void Material::setColor(glm::vec3 color) {
//    _uniforms->setUniformVec3("color", color);
}

std::ostream& operator<<(std::ostream& os, const Material& material) {
    os << *material._meshRender;
    return os;
}
