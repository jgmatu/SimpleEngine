#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <map>

#include "Constants/TypeComp.hpp"

#include "Model/Model.hpp"

#include "Components/Component.hpp"
#include "Components/Camera.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Ligths/Light.hpp"

class Material : public Component {

public:

    Material(Model *model);
    ~Material();

    void start();
    void awakeStart();
    void update();

    void addLigths(std::vector<Light*> ligths);
    void setProgram(Program *program);
    void setTexture(std::string id_mesh, Texture *texture);
    void setColor(glm::vec3 rgb);

    void setView(Camera *camera);

    void setParameter(std::string, glm::vec3);
    void setParameter(std::string, glm::mat4);
    void setParameter(std::string, int);
    void setParameter(std::string, float);

    void setTransparent();
    void setOpaque();
    bool isTransparent();

    friend std::ostream& operator<<(std::ostream& os, const Material& material);

private:

    Material();

    Uniforms *_uniforms;
    Program *_program;
    Model *_model;

    std::map<std::string, std::vector<Texture*>> _textures;

    bool _tranparent;
};

#endif
