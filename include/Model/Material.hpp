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

    void drawTextures();
    void activeTextures(); 

    Uniforms* getUniforms() {
        return this->_uniforms;
    }

    friend std::ostream& operator<<(std::ostream& os, const Material& material);

private:

    size_t sizeTextures();
    void addNewTexture(Texture *texture);
 
    std::vector<Texture*> _textures;

    uint32_t _diffuseNr = 0;
    uint32_t _specularNr = 0;
    uint32_t _normalNr = 0;
    uint8_t _nTexture = 0;

    Uniforms *_uniforms;
};

#endif
