#include "Drawers/Render.hpp"

Render::Render()
{
    this->_uniforms = new Uniforms();
    this->_model = nullptr;
    this->_program = nullptr;
}

Render::~Render()
{
    delete _uniforms;
    delete _program;
    delete _model;
}

bool Render::isTransparentModel()
{
    if (!this->_model) {
        std::cerr << "Null pointr model on is transparent query" << std::endl;
        throw;
    }
    return this->_model->isTransparentModel();
}

void Render::setMatrixModel(glm::mat4 model)
{
    _uniforms->setUniformMat4("model", model);
}

void Render::setModel(Model *model)
{
    this->_model = model;
}

void Render::setProgram(Program *program)
{
    this->_program = program;
}

void Render::setView(Camera *camera)
{
    _uniforms->setUniformMat4("projection", camera->_projection);
    _uniforms->setUniformMat4("view", camera->_view->_gModel);
    _uniforms->setUniformVec3("viewPos", camera->viewPos());
}

void Render::setLigths(std::vector<Light*> ligths)
{
    for (uint32_t i = 0; i < ligths.size(); ++i) {
        _uniforms->update(ligths[i]->getUniforms());
    }
}

void Render::active()
{
    if (!_model || !_program || !_uniforms) {
        std::cerr << "Active Render: Doesn't have a model or material attached" << '\n';
        throw;
    }
    _program->active();
    _model->active();
    if (!_model->isModelLoaded()) {
        std::cerr << "Model not loaded!!" << '\n';
        throw;
    }
}

void Render::draw()
{
    if (!_model || !_program || !_uniforms) {
        std::cerr << "Update Render: Error invalid material or model" << '\n';
        throw;
    }
    _program->use();
    _model->insertModelVariables(_uniforms);
    _program->update(_uniforms);
    _model->draw();
}
