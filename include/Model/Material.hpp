#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <map>

#include "Ligths/Light.hpp"
#include "Components/Camera.hpp"

#include "Program/Program.hpp"
#include "Program/Uniforms.hpp"

#include "Texture.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Material {

public:

    Material();
    ~Material();

    void setTexture(std::string id_mesh, Texture *texture);
    void setProgram(Program *program);
    void setTransparent();
    void setOpaque();

    friend std::ostream& operator<<(std::ostream& os, const Material& material);

private:

    bool isTransparent() const;
    size_t sizeTextures();

    void setParameter(std::string, glm::vec3);
    void setParameter(std::string, glm::mat4);
    void setParameter(std::string, int);
    void setParameter(std::string, float);

    void setView(Camera *camera);
    void update(Material *material);
    void update(Light *ligth);

    Uniforms *_uniforms;
    Program *_program;

    std::map<std::string, std::vector<Texture*>> _textures;
    bool _transparent;

    friend class Model;
    friend class Mesh;
    friend class Render;
};

#endif
