#ifndef RENDER_H
#define RENDER_H

#include "Components/Material.hpp"
#include "Model/Model.hpp"
#include "Program/Program.hpp"

class Render {

public:

    Render();
    ~Render();

private:

    Model *_model;
    Material *_material;
    Program *_program;

};

#endif // RENDER_H
