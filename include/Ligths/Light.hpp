#ifndef LIGHT_H
#define LIGHT_H

#include "Constants/TypeComp.hpp"
#include "Program/Uniforms.hpp"


class Light {

public:

    Light();
    Light(CompLigth type);

    virtual ~Light();

    virtual void setParameters(Uniforms *uniforms) = 0;

    CompLigth _type;

protected:

    glm::vec3 _value;
    std::map<int, glm::vec3> _distances;

};

class Ambient : public Light {

public:

    Ambient();
    Ambient(glm::vec3 value);
    ~Ambient();

    void setParameters(Uniforms *uniforms);

};

class Diffuse : public Light {

public:

    Diffuse();
    Diffuse(glm::vec3 value);
    ~Diffuse();

    void setParameters(Uniforms *uniforms);

};

class Specular : public Light {

public:

    Specular();
    Specular(glm::vec3 value, float shininess);
    ~Specular();

    void setParameters(Uniforms *uniforms);

private:

    float _shininess;
};

class Directional : public Light {

public:

    Directional();
    Directional(glm::vec3 direction);
    ~Directional();

    void setParameters(Uniforms *uniforms);

private:

    glm::vec3 _direction;
};

class Point : public Light {

public:

    Point();
    Point(int num, glm::vec3 position);
    ~Point();

    void setParameters(Uniforms *uniforms);

private:

    int _num;
    glm::vec3 _position;
};

class Spot : public Light {

public:

    Spot();
    Spot(glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff);
    ~Spot();

    void setParameters(Uniforms *uniforms);

private:

    glm::vec3 _position;
    glm::vec3 _direction;
    float _cutOff; // Degrees...
    float _outerCutOff; // Degrees...
};

#endif // LIGHT_H