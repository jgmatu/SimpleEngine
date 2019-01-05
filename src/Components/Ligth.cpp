#include "Components/Light.hpp"

Light::Light()
{
    ;
}

Light::Light(CompLigth type) :
    Light::Light()
{
    this->_type = type;
}

Light::~Light()
{
    ;
}

Ambient::Ambient() :
    Light::Light(CompLigth::AMBIENT)
{
    ;
}
Ambient::Ambient(glm::vec3 value) :
    Ambient::Ambient()
{
    this->_value = value;
}

Ambient::~Ambient()
{
    ;
}

void Ambient::setParameters(Uniforms *uniforms)
{
    uniforms->setUniformVec3("material.ambient", _value);
}

Diffuse::Diffuse() :
    Light::Light(CompLigth::DIFFUSE)
{
    ;
}

Diffuse::Diffuse(glm::vec3 value) :
    Diffuse::Diffuse()
{
    this->_value = value;
}

Diffuse::~Diffuse()
{
    ;
}

void Diffuse::setParameters(Uniforms *uniforms)
{
//    uniforms->setUniformVec3("material.diffuse", _value);
}

Specular::Specular() :
    Light::Light(CompLigth::SPECULAR)
{
    ;
}

Specular::Specular(glm::vec3 value, float shininess) :
    Specular::Specular()
{
    this->_value = value;
    this->_shininess = shininess;
}

Specular::~Specular()
{
    ;
}

void Specular::setParameters(Uniforms *uniforms)
{
//    uniforms->setUniformVec3("material.specular", _value);
    uniforms->setUniformFloat("material.shininess", _shininess);
}


Directional::Directional() :
    Light::Light(CompLigth::DIRECTIONAL)
{
    ;
}

Directional::Directional(glm::vec3 direction) :
    Directional::Directional()
{
    this->_direction = direction;
}

Directional::~Directional()
{
    ;
}

void Directional::setParameters(Uniforms *uniforms)
{
    uniforms->setUniformVec3("directional.direction", this->_direction);
    uniforms->setUniformVec3("directional.ambient", glm::vec3(0.51f));
    uniforms->setUniformVec3("directional.diffuse", glm::vec3(0.51f));
    uniforms->setUniformVec3("directional.specular", glm::vec3(0.51f));
}

Point::Point() :
    Light::Light(CompLigth::POINT)
{
    ;
}

Point::Point(int num, glm::vec3 position) :
    Point::Point()
{
    this->_num = num;
    this->_position = position;
}

Point::~Point()
{
    ;
}

void Point::setParameters(Uniforms *uniforms)
{
    std::string index = std::string(std::to_string(this->_num));

    uniforms->setUniformVec3("points[" + index + "].ambient", glm::vec3(0.6f));
    uniforms->setUniformVec3("points[" + index + "].diffuse", glm::vec3(0.6f));
    uniforms->setUniformVec3("points[" + index + "].specular", glm::vec3(1.0f));
    uniforms->setUniformVec3("points[" + index + "].position", this->_position);

    uniforms->setUniformFloat("points[" + index + "].constant", 1.0f);
    uniforms->setUniformFloat("points[" + index + "].linear", 0.7f);
    uniforms->setUniformFloat("points[" + index + "].quadratic", 1.8f);
}

Spot::Spot() :
    Light::Light(CompLigth::SPOT)
{
    ;
}

Spot::Spot(glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff) :
    Spot::Spot()
{
    this->_position = position;
    this->_direction  = direction;
    this->_cutOff = cutOff;
    this->_outerCutOff = outerCutOff;
}

Spot::~Spot()
{
    ;
}

void Spot::setParameters(Uniforms *uniforms)
{
    uniforms->setUniformVec3("spot.ambient", glm::vec3(0.6f));
    uniforms->setUniformVec3("spot.diffuse", glm::vec3(0.6f));
    uniforms->setUniformVec3("spot.specular", glm::vec3(1.0f));

    uniforms->setUniformVec3("spot.position", this->_position);
    uniforms->setUniformVec3("spot.direction", this->_direction);
    uniforms->setUniformFloat("spot.cutOff", glm::cos(glm::radians(this->_cutOff)));
    uniforms->setUniformFloat("spot.outerCutOff", glm::cos(glm::radians(this->_outerCutOff)));

    uniforms->setUniformFloat("spot.constant", 1.0f);
    uniforms->setUniformFloat("spot.linear", 0.07f);
    uniforms->setUniformFloat("spot.quadratic", 0.017f);
}
