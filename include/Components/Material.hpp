#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#include "Constants/TypeComp.hpp"

#include "Model/Model.hpp"

#include "Components/Component.hpp"
#include "Components/Light.hpp"
#include "Components/Camera.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Material : public Component {

public:

    Material();
    Material(Model *model, Program *program);
    ~Material();

    void start();
    void awakeStart();
    void update();
    void addLigths(std::vector<Light*> ligths);

    void setView(Camera *camera);
    void setViewSkyBox(Camera *camera);

    void setParameter(std::string, glm::vec3);
    void setParameter(std::string, glm::mat4);
    void setParameter(std::string, int);
    void setParameter(std::string, float);

    void setTransparent();
    void setOpaque();
    bool isTransparent();

    friend std::ostream& operator<<(std::ostream& os, const Material& material);

private:

    Uniforms *_uniforms;
    Program *_program;
    Model *_model;

    bool _tranparent;

};

#endif
