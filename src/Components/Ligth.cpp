#include "Components/Light.hpp"


Light::Light() {
    this->_tf = new Transform();
}

Light::Light(float strength, glm::vec3 color, Uniforms *uniforms) :
    Light::Light()
{
    this->strength = strength;
    this->color = color;
    this->_uniforms = uniforms;
}

Light::~Light() {
    ;
}

Ambient::Ambient() :
    Light::Light()
{
    ;
}

                // *** Ambient Ligth *** ///

Ambient::Ambient(float strength, glm::vec3 color, Uniforms *uniforms) :
    Light::Light(strength, color, uniforms)
{
    this->_type = TypeComp::LIGTH_AMBIENT;
}

Ambient::~Ambient()
{
    ;
}

void Ambient::start()
{
    _uniforms->setUniformFloat("ambientStrength", strength);
    _uniforms->setUniformVec3("ambientColor", color);
}

void Ambient::awakeStart()
{
    _uniforms->setUniformFloat("ambientStrength", strength);
    _uniforms->setUniformVec3("ambientColor", color);
}

void Ambient::update()
{
    _uniforms->setUniformFloat("ambientStrength", strength);
    _uniforms->setUniformVec3("ambientColor", color);
}


                // *** Specular Ligth *** ///

Specular::Specular() :
    Light::Light()
{
    this->_type = TypeComp::LIGTH_SPECULAR;
}

Specular::Specular(float strength, glm::vec3 color, Uniforms *uniforms) :
    Light::Light(strength, color, uniforms)
{
    this->_type = TypeComp::LIGTH_SPECULAR;
}

Specular::~Specular()
{
    ;
}

void Specular::start()
{
    _uniforms->setUniformFloat("specularStrength", strength);
    _uniforms->setUniformVec3("specularColor", color);
}

void Specular::awakeStart()
{
    _uniforms->setUniformFloat("specularStrength", strength);
    _uniforms->setUniformVec3("specularColor", color);
}

void Specular::update()
{
    _uniforms->setUniformFloat("specularStrength", strength);
    _uniforms->setUniformVec3("specularColor", color);
}

                // *** Diffuse Ligth *** ///

Diffuse::Diffuse() :
    Light::Light()
{
    this->_type = TypeComp::LIGTH_DIFFUSE;
}

Diffuse::Diffuse(float strength, glm::vec3 color, Uniforms *uniforms) :
    Light::Light(strength, color, uniforms)
{
    this->_type = TypeComp::LIGTH_DIFFUSE;
}

Diffuse::~Diffuse()
{
    ;
}

void Diffuse::start()
{
    _uniforms->setUniformFloat("diffuseStrength", strength);
    _uniforms->setUniformVec3("diffuseColor", color);
}

void Diffuse::awakeStart()
{
    _uniforms->setUniformFloat("diffuseStrength", strength);
    _uniforms->setUniformVec3("diffuseColor", color);
}

void Diffuse::update()
{
    _uniforms->setUniformFloat("diffuseStrength", strength);
    _uniforms->setUniformVec3("diffuseColor", color);
}
