#ifndef RENDER_H
#define RENDER_H

#include "Drawers/Drawer.hpp"
#include "Model/Material.hpp"
#include "Model/Model.hpp"
#include "Program/Program.hpp"
#include "Ligths/Light.hpp"

class Render : public Drawer {

public:

    Render();
    ~Render();

    void active();
    void draw();

    void setModel(Model *model);
    void setProgram(Program *program);
    void setView(Camera *camera);

private:

    friend class GameObject;

    void setMatrixModel(glm::mat4 model);
    bool isTransparentModel();
    void setLigths(std::vector<Light*> ligths);
    void updateIlumination(Uniforms *uniforms);

    Model *_model;
    std::vector<Light*> _ligths;
};

#endif // RENDER_H
