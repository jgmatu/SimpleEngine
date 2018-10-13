#include "GameObjects/Camera.hpp"

Camera::Camera() :
    GameObject::GameObject()
{
    std::cout << "Create Game Object camera" << '\n';
}

Camera::~Camera() {
    std::cout << "Delete gameObject camera" << '\n';
}
