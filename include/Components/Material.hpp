#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#include "Constants/TypeComp.hpp"

#include "Mesh/MeshRender.hpp"
#include "Mesh/Textures.hpp"

#include "Components/Component.hpp"
#include "Components/Light.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Texture;

class Material : public Component {

public:

    Material();
    Material(MeshRender *meshRender);
    ~Material();

    void start();
    void awakeStart();
    void update();

    void setParameter(std::string, glm::vec3);
    void setParameter(std::string, glm::mat4);
    void setParameter(std::string, int);
    void setParameter(std::string, float);

    void setTexture(Texture *texture);
    void setProgram(Program *program);

    void setLigth(Light *ligth);
    void eraseLigth(CompLigth type);

    void setColor(glm::vec3);

    friend std::ostream& operator<<(std::ostream& os, const Material& material);

private:

    Uniforms *_uniforms;
    Program *_program;
    Textures *_textures;
    MeshRender *_meshRender;

    std::vector<Light*> _ligths;

};

#endif
