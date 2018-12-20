#include "Components/Camera.hpp"

Camera::Camera(GameObject *gameObject) :
    _projection(1)
{
    this->_gameObject = gameObject;
    this->_tf = new Transform();
    this->_projection = glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 100.0f);
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
    Component *component = _gameObject->getComponent(TypeComp::TRANSFORM);

    if (Transform *_tfGo = dynamic_cast<Transform*>(component)) {
        this->_tf->_gModel = _tfGo->_gModel * this->_tf->_model;
        this->_tf->_gModel = glm::inverse(this->_tf->_gModel);
    }
}

std::ostream& operator<<(std::ostream& os, const Camera& camera) {
    os << "*** Camera *** " << std::endl;
    os << "G_Model : " << '\n';
    os << glm::to_string(camera._tf->_gModel) << std::endl;
    os << "Model :" << '\n';
    os << glm::to_string(camera._projection) << std::endl;
    os << "*** *** *** *** *** *** ***" << std::endl;
    return os;
}
