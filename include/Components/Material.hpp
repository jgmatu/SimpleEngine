#ifndef MATERIAL_H
#define MATERIAL_H

#include "Program/Program.hpp"
#include "Mesh/MeshRender.hpp"
#include "Components/Component.hpp"

class Material : public Component {

public:

    Material();
    Material(MeshRender *meshRender, Program *program);
    ~Material();

    void start();
    void awakeStart();
    void update();

private:

    friend class GameObject;
    MeshRender *_meshRender;
    Program *_program;

};

#endif
