#ifndef TEXTURES_H
#define TEXTURES_H

#include "Mesh/Texture.hpp"
#include "Program/Uniforms.hpp"

#include <vector>

class Textures {

public:

    Textures();
    ~Textures();

    void active();
    void render();

    void setTexture(Texture *texture);
    void setParameters(Uniforms *uniforms);

private:

    void drawTexture(Texture *texture);
    void loadTexture(Texture *texture);

    std::vector<Texture*> _textures;
};

#endif // TEXTURES_H
