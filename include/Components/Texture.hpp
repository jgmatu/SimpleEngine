#ifndef TEXTURE_H
#define TEXTURE_H

#include "Component.hpp"
#include <glad/glad.h>

class Texture : public Component {

public:

     Texture();
     Texture(std::string filename);
    ~Texture();

    // Este método SOLO se llama una vez la primera vez que se crea el componente.
    void start();

    // Método que se llama cada vez que el Componente se activa.
    void awakeStart();

    // Método que realiza transformaciones, cálculos de cosas.
    void update();

private:

    void loadTexture();
    void drawTexture();

    std::string _filename;

    GLuint _textureID;

};
#endif // TEXTURE_H
