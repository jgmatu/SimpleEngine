#ifndef DRAWER_H
#define DRAWER_H

#include "Model/Material.hpp"
#include "Model/Model.hpp"
#include "Ligths/Light.hpp"

class Drawer {

public:

    virtual ~Drawer() { ; };

    virtual void active() = 0;
    virtual void draw() = 0;
    virtual void setView(Camera *camera) = 0;

protected:

    Program *_program;
    Uniforms *_uniforms;
    Camera *_camera;
};

#endif // DRAWER_H
