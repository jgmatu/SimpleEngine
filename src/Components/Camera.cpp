#include "Components/Camera.hpp"

Camera::Camera() :
    _projection(1)
{
    this->_view = new Transform();
    this->_projection = glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 100.0f);
}

Camera::~Camera()
{
    std::cout << "Delete component camera" << '\n';
}

void Camera::start()
{
    this->_view->_gModel = glm::translate(this->_view->_gModel, glm::vec3(0, 0, 5.0));
}

void Camera::update()
{
    if (!_tfObj) {
        std::cerr << "The camera is not attached to a gameObject" << '\n';
        throw;
    }
    // Tracker camera, de un gameObject
    _view->_gModel = _tfObj->_gModel * _view->_model;
    _view->_gModel = glm::inverse(_view->_gModel);
}

void Camera::translate(glm::vec3 vec3)
{
    this->_view->_model = glm::translate(this->_view->_model, vec3);
}
void Camera::rotate(glm::vec3 vec3, float angle)
{
     this->_view->_model = glm::rotate(this->_view->_model, angle, vec3);
}


glm::vec3 Camera::viewPos()
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
