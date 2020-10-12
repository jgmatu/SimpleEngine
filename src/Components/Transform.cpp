#include "Components/Transform.hpp"

Transform::Transform() :
    _gModel(1.0f),
    _model(1.0f),
    _last_model(1.0f),
    _inital_position(1.0f)
{
    ;
}

Transform::~Transform()
{
    std::cout << "Delete component transform" << '\n';
}

void Transform::start()
{
    for (uint32_t i = 0; i < tfChilds.size(); ++i) {
        tfChilds[i]->_gModel = _gModel * tfChilds[i]->_model;
    }
    this->_inital_position = this->_model;
    this->_last_model = this->_model;
}

void Transform::addChild(Transform *tf)
{
    tfChilds.push_back(tf);
}

bool Transform::isMove(glm::mat4 model, glm::mat4 last_model)
{
    for (uint32_t i = 0; i < 4; ++i) {
        for (uint32_t j = 0; j < 4; ++j) {
            if (fabs(model[i][j] - last_model[i][j]) > 0.01) {
                return true;
            }
        }
    }
    return false;
}

void Transform::update()
{
    for (uint32_t i = 0; i < tfChilds.size(); ++i) {
        tfChilds[i]->_gModel = _gModel * tfChilds[i]->_model;
    }
    // Reset relative matrix model to start new dependency operations on next iterations.
    if (isMove(this->_model, this->_last_model) || isMove(this->_gModel, this->_inital_position)) {
        this->_model = glm::mat4(1.0);
    }
    this->_last_model = this->_model;
}

glm::vec3 Transform::position() const {
    return this->_gModel[3];
}

std::ostream& operator<<(std::ostream& os, const Transform& tf) {
    os << "Model : " << std::endl << glm::to_string(tf._model) << std::endl;
    os << "GModel : " << std::endl << glm::to_string(tf._gModel) << std::endl;
    os << "Position : " << std::endl << glm::to_string(tf.position()) << std::endl;
    return os;
}
