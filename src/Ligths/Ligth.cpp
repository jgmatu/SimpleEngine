#include "Ligths/Light.hpp"

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
    this->_uniforms = new Uniforms();
}

Light::~Light()
{
    delete this->_uniforms;
}

bool Light::isLigth(std::string id)
{
    return this->_id.compare(id) == 0;
}

Uniforms* Light::getUniforms()
{
    return this->_uniforms;
}


Directional::Directional()
{
    ;
}

Directional::Directional(std::string id) :
    Directional::Directional()
{
    this->_id = id;
}

Directional::~Directional()
{
    ;
}

void Directional::setDirection(glm::vec3 direction)
{
    this->_uniforms->setUniformVec3("directional.direction", direction);
}

void Directional::setPosition(glm::vec3 position)
{
    std::cerr << "Directional doesn't have a position" << '\n';
    throw;
}

void Directional::setDistance(int distance)
{
    std::cerr << "Directional distance doesn't have a distance" << '\n';
    throw;
}

void Directional::setIntense(float percentage)
{
    this->_uniforms->setUniformVec4("directional.diffuse", percentage * glm::vec4(1.0f));
    this->_uniforms->setUniformVec4("directional.specular", percentage *  glm::vec4(1.0f));
}

Point::Point()
{
    ;
}

Point::Point(std::string id) :
    Point::Point()
{
    this->_id = id;
    this->_index = Point::_num++;

    if (Point::_num == MAX_POINT_LIGHTS) {
        std::cerr << "Error limit points in engine!" << '\n';
        throw;
    }
    std::cerr << "npoints " << Point::_num << '\n';
    this->_uniforms->setUniformInt("npoints", Point::_num);
}

Point::~Point()
{
    ;
}

void Point::setPosition(glm::vec3 position)
{
    std::string index = std::string(std::to_string(this->_index));

    this->_uniforms->setUniformVec3("points[" + index + "].position", position);
}

void Point::setDistance(int distance)
{
    glm::vec3 _distance = _distances[distance];
    std::string index = std::string(std::to_string(this->_index));

    this->_uniforms->setUniformFloat("points[" + index + "].constant", _distance[0]);
    this->_uniforms->setUniformFloat("points[" + index + "].linear", _distance[1]);
    this->_uniforms->setUniformFloat("points[" + index + "].quadratic", _distance[2]);
}

void Point::setDirection(glm::vec3 direction)
{
    std::cerr << "Point doesn't have direction" << '\n';
    throw;
}

void Point::setIntense(float percentage)
{
    std::string index = std::string(std::to_string(this->_index));

    this->_uniforms->setUniformVec4("points[" + index + "].diffuse", percentage * glm::vec4(1.0f));
    this->_uniforms->setUniformVec4("points[" + index + "].specular", percentage * glm::vec4(1.0f));
}

Spot::Spot()
{
    ;
}

Spot::Spot(std::string id, float cutOff, float outerCutOff) :
    Spot::Spot()
{
    this->_id = id;
    this->_uniforms->setUniformFloat("spot.cutOff", glm::cos(glm::radians(cutOff)));
    this->_uniforms->setUniformFloat("spot.outerCutOff", glm::cos(glm::radians(outerCutOff)));
}

Spot::~Spot()
{
    ;
}

void Spot::setPosition(glm::vec3 position)
{
    this->_uniforms->setUniformVec3("spot.position", position);
}

void Spot::setDirection(glm::vec3 direction)
{
    this->_uniforms->setUniformVec3("spot.direction", direction);
}

void Spot::setIntense(float percentage)
{
    this->_uniforms->setUniformVec4("spot.diffuse", percentage * glm::vec4(1.0f));
    this->_uniforms->setUniformVec4("spot.specular", percentage * glm::vec4(1.0f));
}

void Spot::setDistance(int distance)
{
    glm::vec3 _distance = _distances[distance];

    this->_uniforms->setUniformFloat("spot.constant", _distance[0]);
    this->_uniforms->setUniformFloat("spot.linear", _distance[1]);
    this->_uniforms->setUniformFloat("spot.quadratic", _distance[2]);
}
