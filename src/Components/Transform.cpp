#include "Components/Transform.hpp"

Transform::Transform() :
    _gModel(1.0f),
    _model(1.0f)
{
    this->_type = TypeComp::TRANSFORM;
}

Transform::~Transform() {
    ;
}

void Transform::start()
{
    ;
}

void Transform::awakeStart() {
    ;
}

void Transform::update() {
    this->_model = getInitialPosition();

    for (unsigned i = 0; i < this->_moves.size(); ++i) {
        this->_model = this->_model * this->_moves[i]->apply();
    }
}

glm::mat4 Transform::getInitialPosition()
{
    glm::mat4 _initialModel(1.0);

    for (unsigned i = 0; i < _position.size(); ++i) {
        _initialModel = _initialModel * _position[i]->apply();
    }
    return _initialModel;
}

void Transform::init(glm::vec3 axis, float angle)
{
    this->_position.push_back(new Position(axis, angle));
}

void Transform::init(glm::vec3 position)
{
    this->_position.push_back(new Position(position));
}

void Transform::scale(glm::vec3 vec3) {
    this->_moves.push_back(new Scale(vec3));
};

void Transform::translate(glm::vec3 vec3) {
    this->_moves.push_back(new Translate(vec3));
}

void Transform::rotate(glm::vec3 vec3, glm::quat quat) {
    this->_moves.push_back(new Rotate(vec3, quat));
}

void Transform::rotate(glm::vec3 vec3, float angle) {
    this->_moves.push_back(new Rotate(angle, vec3));
}

glm::vec3 Transform::position() const {
    glm::mat4 mat4 = -this->_gModel;
    glm::vec3 row = mat4[3];
    std::cout << "Position : " << row.x << " " << row.y << " " << row.z << '\n';
    return glm::vec3(row.x, row.y, row.z);
}

std::ostream& operator<<(std::ostream& os, const Transform& tf) {
    os << "Model : " << std::endl << glm::to_string(tf._model) << std::endl;
    os << "GModel : " << std::endl << glm::to_string(tf._gModel) << std::endl;
    os << "Position : " << std::endl << glm::to_string(tf.position()) << std::endl;
    return os;
}
