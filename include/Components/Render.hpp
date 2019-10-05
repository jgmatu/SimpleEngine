#ifndef RENDER_H
#define RENDER_H

#include "Model/Material.hpp"
#include "Model/Model.hpp"
#include "Program/Program.hpp"
#include "Ligths/Light.hpp"

class Render : public Component {

public:

    Render();
    ~Render();

    void start();
    void awakeStart();
    void update();

    void setModel(Model *model);
    void setMaterial(Material *material);

private:

    friend class GameObject;

    void setMatrixModel(glm::mat4 model);
    bool isMaterialTransparent();
    void setView(Camera *camera);
    void setLigths(std::vector<Light*> ligths);

    Model *_model;
    Material *_material;

};

#endif // RENDER_H
