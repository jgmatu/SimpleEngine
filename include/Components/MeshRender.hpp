#ifndef RENDER_H
#define RENDER_H

#include "Model/Material.hpp"
#include "Model/Model.hpp"
#include "Program/Program.hpp"
#include "Ligths/Light.hpp"

class MeshRender : public Component {

public:

    MeshRender();
    ~MeshRender();

    void start();
    void awakeStart();
    void update();

    void setProgram(Program *program);
    void setModel(Model *model);

    void setMaterial(Material *material);
    Material* getMaterial();

    void setMatrixModel(glm::mat4 model);

    bool isMaterialTransparent();

    void setView(Camera *camera);
    void setLigths(std::vector<Light*> ligths);

private:

    Model *_model;
    Material *_material;

};

#endif // RENDER_H
