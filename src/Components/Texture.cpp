#include "Components/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

Texture::Texture()  {
    this->_type = TypeComp::TEXTURE;
}

Texture::Texture(std::string filename) :
    Texture::Texture()
{
    this->_filename = filename;
}

Texture::~Texture() {
    ;
}

// Este método SOLO se llama una vez la primera vez que se crea el componente.
void Texture::start() {
    this->loadTexture();
}

// Método que se llama cada vez que el Componente se activa.
void Texture::awakeStart() {
    this->drawTexture();
}

// Método que realiza transformaciones, cálculos de cosas.
void Texture::update() {
    this->drawTexture();
}

void Texture::drawTexture() {
    glActiveTexture(GL_TEXTURE0); // Activate first texture unit... diffuseTexture 0.
    glBindTexture(GL_TEXTURE_2D, _textureID);
}

void Texture::loadTexture() {
    std::ifstream file(this->_filename);

    if (file.fail()) {
        std::cerr << "Texture file not exists" << '\n';
        throw;
    }
    int width, heigth, channels;
    unsigned char* pixels = stbi_load(this->_filename.c_str(), &width, &heigth, &channels, 0);

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID); // all upcoming GL_TEXTURE_2D operations now have

    // set the texture wrapping parameters.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    } else if (channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    }
    free(pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
}
