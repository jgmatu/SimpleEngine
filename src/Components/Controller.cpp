#include "Components/Controller.hpp"

Controller::Controller() :
    _cameras()
{
    _camera = 0;
}

Controller::~Controller()
{
    ;
}

void Controller::start()
{
    ;
}

void Controller::update()
{
    ;
}

void Controller::changeCamera()
{
    this->_camera = (this->_camera + 1) % this->_cameras.size();
}

void Controller::initCameras(std::vector<Camera*> cameras)
{
    _cameras = cameras;
}

Camera* Controller::getActiveCamera()
{
    return this->_cameras[this->_camera];
}