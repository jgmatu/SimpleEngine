#include "Components/Transform.hpp"

Transform::Transform() :
    _pos("(0, 0 ,0)"),
    _scale("(1, 1, 1)"),
    _axis("(0, 0, 0)"),
    _quat("0")
{
    this->_type = TypeComp::TRANSFORM;
    std::cout << "************ Transform ***************" << '\n';
}

Transform::~Transform() {
    ;
}

void Transform::start() {
    std::cout << "**** Transform start ****" << '\n';
    std::cout << "-> Position " << _pos << '\n';
    std::cout << "-> Scale " << _scale << '\n';
    std::cout << "-> Axis " << _axis << '\n';
    std::cout << "-> Quat " << _quat << '\n';
}

void Transform::awakeStart() {
    std::cout << "Component Transform awakeStart..." << '\n';
}

void Transform::update() {
    std::cout << "**** Transform update **** " << '\n';
    std::cout << "-> Position " << _pos << '\n';
    std::cout << "-> Scale " << _scale << '\n';
    std::cout << "-> Axis " << _axis << '\n';
    std::cout << "-> Quat " << _quat << '\n';
}

void Transform::scale(std::string vec3) {
    this->_scale = vec3;
};

void Transform::translate(std::string vec3) {
    this->_pos = vec3;
}

void Transform::rotate(std::string vec3, std::string quat) {
    this->_quat = quat;
    this->_axis = vec3;
}
