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
//    uniforms->setUniformVec3("material.ambient", _value);
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
    uniforms->setUniformVec3("material.diffuse", _value);
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
    uniforms->setUniformVec3("material.specular", _value);
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

    uniforms->setUniformVec3("directional.ambient", glm::vec3(0.1f));
    uniforms->setUniformVec3("directional.diffuse", glm::vec3(1.0f));
    uniforms->setUniformVec3("directional.specular", glm::vec3(1.0f));
}

Point::Point() :
    Light::Light(CompLigth::POINT)
{
    ;
}

Point::Point(glm::vec3 position) :
    Point::Point()
{
    this->_position = position;
}

Point::~Point()
{
    ;
}

void Point::setParameters(Uniforms *uniforms)
{
    uniforms->setUniformVec3("point.ambient", glm::vec3(0.1f));
    uniforms->setUniformVec3("point.diffuse", glm::vec3(1.0f));
    uniforms->setUniformVec3("point.specular", glm::vec3(1.0f));
    uniforms->setUniformVec3("point.position", this->_position);

    uniforms->setUniformFloat("point.constant", 1.0f);
    uniforms->setUniformFloat("point.linear", 0.14f);
    uniforms->setUniformFloat("point.quadratic", 0.07f);
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
    uniforms->setUniformVec3("spot.ambient", glm::vec3(0.1f));
    uniforms->setUniformVec3("spot.diffuse", glm::vec3(1.0f));
    uniforms->setUniformVec3("spot.specular", glm::vec3(1.0f));

    uniforms->setUniformVec3("spot.position", this->_position);
    uniforms->setUniformVec3("spot.direction", this->_direction);
    uniforms->setUniformFloat("spot.cutOff", glm::cos(glm::radians(this->_cutOff)));
    uniforms->setUniformFloat("spot.outerCutOff", glm::cos(glm::radians(this->_outerCutOff)));

    uniforms->setUniformFloat("spot.constant", 1.0f);
    uniforms->setUniformFloat("spot.linear", 0.0014f);
    uniforms->setUniformFloat("spot.quadratic", 0.000007f);
}

LightScene::LightScene() :
    Light::Light(CompLigth::SCENE)
{
    this->_tf = new Transform();
}

LightScene::LightScene(glm::vec3 position) :
    LightScene::LightScene()
{
    this->_tf->_gModel = glm::translate(this->_tf->_gModel, position);
}

LightScene::~LightScene()
{
    delete this->_tf;
}

void LightScene::setParameters(Uniforms *uniforms)
{
    uniforms->setUniformVec3("light.position", this->_tf->position());

//    uniforms->setUniformVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
//    uniforms->setUniformVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
//    uniforms->setUniformVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    uniforms->setUniformVec3("light.ambient", glm::vec3(1.0f));
    uniforms->setUniformVec3("light.diffuse", glm::vec3(1.0f));
    uniforms->setUniformVec3("light.specular", glm::vec3(1.0f));
}
