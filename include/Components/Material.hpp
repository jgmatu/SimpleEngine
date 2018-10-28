#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#include "Program/Program.hpp"
#include "Mesh/MeshRender.hpp"
#include "Components/Component.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Material : public Component {

public:

    Material();
    Material(MeshRender *meshRender, Program *program);
    ~Material();

    void start();
    void awakeStart();
    void update();

    void createUniform(std::string uniformName);

    void setUniform(std::string name, glm::vec3 value);
    void setUniform(std::string name, glm::mat4 value);
    void setUniform(std::string name, int value);

    void addTexture(const char *filename);

    friend std::ostream& operator<<(std::ostream& os, const Material& material);

private:

    MeshRender *_meshRender;
    Program *_program;

};

#endif
