#include "Components/Light.hpp"

Light::Light()
{
    this->_distances = {
        {7, glm::vec3(1.0f, 0.7f, 1.8f)},
        {13, glm::vec3(1.0f, 0.35f, 0.44f)},
        {20, glm::vec3(1.0f, 0.22f, 0.20f)},
        {32, glm::vec3(1.0f, 0.14f, 0.07f)},
        {50, glm::vec3(1.0f, 0.09f, 0.032f)},
        {65, glm::vec3(1.0f, 0.07f, 0.017f)},
        {100, glm::vec3(1.0f, 0.045f, 0.0075f)},
        {160, glm::vec3(1.0f, 0.027f, 0.0028f)},
        {200, glm::vec3(1.0f, 0.022f, 0.0019f)},
        {325, glm::vec3(1.0f, 0.014f, 0.0007f)},
        {600, glm::vec3(1.0f, 0.007f, 0.0002f)},
        {3250, glm::vec3(1.0f, 0.0014f, 0.000007f)}
    };
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
    uniforms->setUniformVec3("directional.ambient", glm::vec3(0.01f));
    uniforms->setUniformVec3("directional.diffuse", glm::vec3(0.01f));
    uniforms->setUniformVec3("directional.specular", glm::vec3(0.01f));
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
    glm::vec3 distance = _distances[3250];

    uniforms->setUniformVec3("points[" + index + "].ambient", glm::vec3(0.0f));
    uniforms->setUniformVec3("points[" + index + "].diffuse", glm::vec3(0.5f));
    uniforms->setUniformVec3("points[" + index + "].specular", glm::vec3(0.8f));
    uniforms->setUniformVec3("points[" + index + "].position", this->_position);

    uniforms->setUniformFloat("points[" + index + "].constant", distance[0]);
    uniforms->setUniformFloat("points[" + index + "].linear", distance[1]);
    uniforms->setUniformFloat("points[" + index + "].quadratic", distance[2]);
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
