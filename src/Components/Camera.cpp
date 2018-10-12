#include "Components/Camera.hpp"

Camera::Camera() {
    std::cout << "Create component camera" << '\n';
}

Camera::~Camera() {
    std::cout << "Delete component camera" << '\n';
}

void Camera::start() {
    std::cout << "Component camera start..." << '\n';
}

void Camera::awakeStart() {
    std::cout << "Component camera awakeStart..." << '\n';
}

void Camera::update() {
    std::cout << "Component camera update..." << '\n';
}
