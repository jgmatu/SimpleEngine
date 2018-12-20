#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#include "Mesh/MeshRender.hpp"
#include "Components/Component.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Material : public Component {

public:

    Material();
    Material(MeshRender *meshRender, Program *program, Uniforms *uniforms);
    ~Material();

    void start();
    void awakeStart();
    void update();

    void setParameter(std::string, glm::vec3);
    void setParameter(std::string, glm::mat4);
    void setParameter(std::string, int);

    void addTexture(const char *filename);

    friend std::ostream& operator<<(std::ostream& os, const Material& material);

private:

    MeshRender *_meshRender;
};

#endif
