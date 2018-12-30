#include "Components/Transform.hpp"

Transform::Transform() :
    _gModel(1.0f),
    _model(1.0f)
{
    this->_type = TypeComp::TRANSFORM;
}

Transform::~Transform() {
    ;
}

void Transform::start()
{
    ;
}

void Transform::awakeStart() {
    ;
}

void Transform::update() {
    this->_model = glm::mat4(1.0f);

    for (unsigned i = 0; i < this->_operations.size(); ++i) {
        this->_model = this->_model * this->_operations[i]->apply();
        delete this->_operations[i];
    }
    this->_operations.erase(this->_operations.begin(), this->_operations.end());
}

void Transform::scale(glm::vec3 vec3) {
    this->_operations.push_back(new Scale(vec3));
};

void Transform::translate(glm::vec3 vec3) {
    this->_operations.push_back(new Translate(vec3));
}

void Transform::rotate(glm::vec3 vec3, glm::quat quat) {
    this->_operations.push_back(new Rotate(vec3, quat));
}

void Transform::rotate(glm::vec3 vec3, float angle) {
    this->_operations.push_back(new Rotate(angle, vec3));
}

glm::vec3 Transform::position() {
    glm::vec4 row = this->_gModel[3];

    return glm::vec3(row.x, row.y, row.z);
}

std::ostream& operator<<(std::ostream& os, const Transform& tf) {
    os << "Model : " << std::endl << glm::to_string(tf._model) << std::endl;
    os << "GModel : " << std::endl << glm::to_string(tf._gModel) << std::endl;
    return os;
}
