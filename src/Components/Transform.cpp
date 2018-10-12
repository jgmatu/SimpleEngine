#include "Components/Transform.hpp"

Transform::Transform() {
    std::cout << "************ Transform ***************" << '\n';
}

Transform::~Transform() {
    ;
}

void Transform::start() {
    std::cout << "Component Transform start..." << '\n';
}

void Transform::awakeStart() {
    std::cout << "Component Transform awakeStart..." << '\n';
}

void Transform::update() {
    std::cout << "Component Transform update..." << '\n';
}
