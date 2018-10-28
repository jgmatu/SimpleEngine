#include "GameObjects/Camera.hpp"

Camera::Camera() :
    GameObject::GameObject(),
    _view(1),
    _projection(1)
{
    this->_id = 100;
    this->_name = "**** CAMERA **** ";
    this->_projection = glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 100.0f);

    this->_view = glm::mat4(1.0);
    this->_view = glm::translate(glm::vec3(0.0, 0.0, -15.0));
}

Camera::~Camera() {
    std::cout << "Delete gameObject camera" << '\n';
}

std::ostream& operator<<(std::ostream& os, const Camera& camera) {
    os << "*** Camera *** " << std::endl;
    os << glm::to_string(camera._view) << std::endl;
    os << glm::to_string(camera._projection) << std::endl;
    os << "*** *** *** *** *** *** ***" << std::endl;
    return os;
}
