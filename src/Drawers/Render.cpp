#include "Drawers/Render.hpp"

Render::Render()
{
    this->_model = nullptr;
    this->_material = nullptr;
}

Render::~Render()
{
    delete _material;
    delete _model;
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

void Render::active()
{
    if (_model && _material) {
        if (_material->sizeTextures() == 0) {
            std::cerr << "Active Render: Doesn't have textures attached" << '\n';
            return;
        }
        _model->setMaterial(_material);
        _model->active();
    } else {
        std::cerr << "Active Render: Doesn't have a model or material attached" << '\n';
    }
}

void Render::draw()
{
    if (!_model || !_material) {
        std::cerr << "Update Render: Error invalid material or model" << '\n';
        return;
    }
    if (_material->sizeTextures() > 0) {
        _model->updateMaterial(_material);
        _model->draw();
    }
}
