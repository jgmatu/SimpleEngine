#include "Components/Camera.hpp"

Camera::Camera() :
    _projection(1)
{
    this->_type = TypeComp::CAMERA;
    this->_view = new Transform();
    this->_projection = glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 100.0f);
    this->_view->_gModel = glm::translate(glm::vec3(0.0, 0.0, -10.0));
}

Camera::~Camera()
{
    std::cout << "Delete gameObject camera" << '\n';
}

// Este método SOLO se llama una vez la primera vez que se crea el componente.
void Camera::start() {
    ;
}

// Método que se llama cada vez que el Componente se activa.
void Camera::awakeStart() {
    ;
}

// Método que realiza transformaciones, cálculos de cosas.
void Camera::update() {
    ;
}

std::ostream& operator<<(std::ostream& os, const Camera& camera) {
    os << "G_Model : " << '\n';
    os << glm::to_string(camera._view->_gModel) << std::endl;
    os << "Model :" << '\n';
    os << glm::to_string(camera._projection) << std::endl;
    return os;
}
