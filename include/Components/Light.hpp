#ifndef LIGHT_H
#define LIGHT_H

#include "Transform.hpp"

class Light : public Component {

public:

    Light();
    Light(float strength, glm::vec3 color, Uniforms *uniforms);

    ~Light();

    // Este método SOLO se llama una vez la primera vez que se crea el componente...
    virtual void start() = 0;

    // Método que se llama cada vez que el componente se activa...
    virtual void awakeStart() = 0;

    // Método que realiza transformaciones, cálculos de cosas...
    virtual void update() = 0;

protected:

    Transform *_tf;
    float strength;
    glm::vec3 color;

};

class Ambient : public Light {

public:

    Ambient();
    Ambient(float strength, glm::vec3 color, Uniforms *uniforms);

    ~Ambient();

    void start();
    void awakeStart();
    void update();

};

class Diffuse : public Light {

public:

    Diffuse();
    Diffuse(float strength, glm::vec3 color, Uniforms *uniforms);

    ~Diffuse();
    void start();
    void awakeStart();
    void update();
};

class Specular : public Light {

public:

    Specular();
    Specular(float strength, glm::vec3 color, Uniforms *uniforms);

    ~Specular();
    void start();
    void awakeStart();
    void update();
};

#endif // LIGHT_H
