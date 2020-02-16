#include "Components/Transform.hpp"

Transform::Transform() :
    _gModel(1.0f),
    _model(1.0f)
{
    ;
}

Transform::~Transform()
{
    std::cout << "Delete component transform" << '\n';
}

void Transform::start()
{
    ;
}

void Transform::addChild(Transform *tf)
{
    tfChilds.push_back(tf);
}

void Transform::update()
{
    for (uint32_t i = 0; i < tfChilds.size(); ++i) {
        tfChilds[i]->_gModel = _gModel * tfChilds[i]->_model;
    }
    // Reset relative matrix model to start new 
    // dependency operations on next iterations...
    this->_model = glm::mat4(1.0);
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
