#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>

#include "Program/Uniforms.hpp"

class Light {

public:

    virtual ~Light();

    virtual void setIntense(float percentage) = 0;
    virtual void setPosition(glm::vec3 position) = 0;
    virtual void setDirection(glm::vec3 direction) = 0;
    virtual void setDistance(int distance) = 0;

    // Common functions
    bool isLigth(std::string id);
    Uniforms* getUniforms();

protected:

    Light();

    std::string _id;
    Uniforms *_uniforms;
    std::map<int, glm::vec3> _distances;

    friend class Scene;
};

class Directional : public Light {

public:

    Directional(std::string id);
    ~Directional();

    void setIntense(float percentage);
    void setPosition(glm::vec3 position);
    void setDirection(glm::vec3 direction);
    void setDistance(int distance);

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
    void setDistance(int distance);

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
    void setDistance(int distance);

private:

    Spot();

};

#endif // LIGHT_H
