#include "Components/Transform.hpp"

Transform::Transform() :
    _gModel(1),
    _model(1),
    _pos(0, 0, 0),
    _scale(1, 1, 1),
    _axis(0, 0, 0),
    _quat()
{
    this->_type = TypeComp::TRANSFORM;
    std::cout << "************ Transform ***************" << '\n';
}

Transform::~Transform() {
    ;
}

void Transform::start() {
    std::cout << "**** Transform start ****" << '\n';
//    std::cout << "-> Position " << _pos << '\n';
//    std::cout << "-> Scale " << _scale << '\n';
//    std::cout << "-> Axis " << _axis << '\n';
//    std::cout << "-> Quat " << _quat << '\n';
}

void Transform::awakeStart() {
    std::cout << "Component Transform awakeStart..." << '\n';
}

void Transform::update() {
    std::cout << "**** Transform update **** " << '\n';
    _model = glm::translate(_pos);
}

void Transform::scale(glm::vec3 vec3) {
    this->_scale = vec3;
};

void Transform::translate(glm::vec3 vec3) {
    this->_pos.x += vec3.x;
    this->_pos.y += vec3.y;
    this->_pos.z += vec3.z;
}

void Transform::rotate(glm::vec3 vec3, glm::quat quat) {
    this->_quat = quat;
    this->_axis = vec3;
}

glm::mat4 Transform::model() {
    return _model;
};

std::ostream& operator<<(std::ostream& os, const Transform& tf) {
    std::cout << "Pos : (" << tf._pos.x << "," << tf._pos.y << "," << tf._pos.z << ")" << '\n';
    std::cout << "Scale : (" << tf._pos.x << "," << tf._pos.y << "," << tf._pos.z << ")" << '\n';
    std::cout << "Axis : (" << tf._pos.x << "," << tf._pos.y << "," << tf._pos.z << ")" << '\n';
    return os;
}
