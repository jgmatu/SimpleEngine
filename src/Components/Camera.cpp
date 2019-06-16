#include "Components/Camera.hpp"

Camera::Camera() :
    _projection(1)
{
    this->_type = TypeComp::CAMERA;
    this->_view = new Transform();
    this->_projection = glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 100.0f);
}

Camera::~Camera()
{
    std::cout << "Delete component camera" << '\n';
}

// Este método SOLO se llama una vez la primera vez que se crea el componente.
void Camera::start()
{
    this->_view->_gModel = glm::translate(this->_view->_gModel, glm::vec3(0, 0, 5.0));
}

// Método que se llama cada vez que el Componente se activa.
void Camera::awakeStart()
{
    ;
}

// Método que realiza transformaciones, cálculos de cosas.
void Camera::update(Keyboard *keyboard, Clock *clock)
{
    if (!_tfObj) {
        std::cerr << "The camera is not attached to a GameObject" << '\n';
        throw;
    }
    std::cout << "update camera..." << '\n';
    _view->_gModel = _tfObj->_gModel * _view->_model;
}

glm::vec3 Camera::position()
{
    return this->_view->position() * (-1);
}

std::ostream& operator<<(std::ostream& os, const Camera& camera) {
    os << "G_Model : " << '\n';
    os << glm::to_string(camera._view->_gModel) << std::endl;
    os << "Model :" << '\n';
    os << glm::to_string(camera._projection) << std::endl;
    return os;
}
