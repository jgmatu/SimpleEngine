#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>

#include "Constants/TypeComp.hpp"
#include "Program/Uniforms.hpp"

class Light {

public:

    virtual ~Light();

    virtual void setIntense(float percentage) = 0;
    virtual void setPosition(glm::vec3 position) = 0;
    virtual void setDirection(glm::vec3 direction) = 0;
    virtual void setDistance() = 0;

    bool isLigth(std::string id);
    Uniforms* getUniforms();

    CompLigth _type;

protected:

    Light();
    Light(CompLigth type);

    std::string _id;
    Uniforms *_uniforms;
    std::map<int, glm::vec3> _distances;

};

class Directional : public Light {

public:

    Directional(std::string id);
    ~Directional();

    void setIntense(float percentage);
    void setPosition(glm::vec3 position);
    void setDirection(glm::vec3 direction);
    void setDistance();

private:

    Directional();

};

class Point : public Light {

public:

    Point(std::string _id);
    ~Point();

    void setIntense(float percentage);
    void setPosition(glm::vec3 position);
    void setDirection(glm::vec3 direction);
    void setDistance();

private:

    Point();

    const uint32_t MAX_POINT_LIGHTS = 255;
    inline static uint32_t _num;

    uint32_t _index;

};

class Spot : public Light {

public:

    Spot(std::string id, float cutOff, float outerCutOff);
    ~Spot();

    void setIntense(float percentage);
    void setPosition(glm::vec3 position);
    void setDirection(glm::vec3 direction);
    void setDistance();

private:

    Spot();

};

#endif // LIGHT_H
