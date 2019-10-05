#include "Components/Render.hpp"

Render::Render()
{
    this->_type = CompType::MESH_RENDER;
    this->_model = nullptr;
    this->_material = nullptr;
}

Render::~Render()
{
    ;
}

bool Render::isMaterialTransparent()
{
    return this->_material->isTransparent();
}

void Render::setMatrixModel(glm::mat4 model)
{
    this->_material->setParameter("model", model);
}

void Render::setModel(Model *model)
{
    this->_model = model;
}

void Render::setMaterial(Material *material)
{
    this->_material = material;
}

void Render::setView(Camera *camera)
{
    _material->setView(camera);
}

void Render::setLigths(std::vector<Light*> ligths)
{
    for (uint32_t i = 0; i < ligths.size(); ++i) {
        _material->update(ligths[i]);
    }
}

void Render::start()
{
    if (_model && _material) {
        if (_material->sizeTextures() == 0) {
            std::cerr << "Start Render: Doesn't have a model or material attached" << '\n';
            return;
        }
        _model->setMaterial(_material);
        _model->active();
    }
}

void Render::awakeStart()
{
    ;
}

void Render::update()
{
    if (!_model || !_material) {
        std::cerr << "Update Render: Error invalid material or model" << '\n';
        throw;
    }
    if (_material->sizeTextures() > 0) {
        _model->update(_material);
        _model->draw();
    }
}
