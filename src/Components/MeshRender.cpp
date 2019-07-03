#include "Components/MeshRender.hpp"

MeshRender::MeshRender()
{
    this->_type = CompType::MESH_RENDER;
    this->_model = nullptr;
    this->_material = nullptr;
}

MeshRender::~MeshRender()
{
    ;
}

bool MeshRender::isMaterialTransparent()
{
    return this->_material->isTransparent();
}

void MeshRender::setMatrixModel(glm::mat4 model)
{
    this->_material->setParameter("model", model);
}

void MeshRender::setModel(Model *model)
{
    this->_model = model;
}

void MeshRender::setMaterial(Material *material)
{
    this->_material = material;
}

Material* MeshRender::getMaterial()
{
    return this->_material;
}

void MeshRender::setView(Camera *camera)
{
    _material->setView(camera);
}

void MeshRender::setLigths(std::vector<Light*> ligths)
{
    for (uint32_t i = 0; i < ligths.size(); ++i) {
        _material->update(ligths[i]);
    }
}

void MeshRender::start()
{
    if (_model && _material) {
        if (_material->sizeTextures() == 0) {
            std::cerr << "Start : Material: Doesn't have textures attached" << '\n';
        }
        _model->setMaterial(_material);
        _model->active();
    }
}

void MeshRender::awakeStart()
{
    if (_model && _material) {
        _model->update(_material);
        _model->draw();
    } else {
        std::cerr << "Error invalid material or model" << '\n';
        throw;
    }
}

void MeshRender::update()
{
    if (_model && _material) {
        _model->update(_material);
        _model->draw();
    } else {
        std::cerr << "Error invalid material or model" << '\n';
        throw;
    }
}
