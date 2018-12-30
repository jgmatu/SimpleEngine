#include "Mesh/Textures.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Textures::Textures() :
    _textures()
{
    ;
}

Textures::~Textures()
{
    for (unsigned i = 0; i < _textures.size(); ++i) {
        delete _textures[i];
    }
    _textures.clear();
}

void Textures::active()
{
    for (unsigned i = 0; i < _textures.size(); ++i) {
        this->loadTexture(_textures[i]);
    }
}

void Textures::render()
{
    for (unsigned i = 0; i < _textures.size(); ++i) {
        this->drawTexture(_textures[i]);
    }
}

void Textures::setParameters(Uniforms *uniforms)
{
    for (unsigned i = 0; i < _textures.size(); ++i) {
        // Active Texture num same as texture active...
        uniforms->setUniformInt( _textures[i]->_name, _textures[i]->_num);
    }
}

void Textures::drawTexture(Texture *texture)
{
    if (texture->_num == 0) {
        glActiveTexture(GL_TEXTURE0); // Activate first texture unit... diffuseTexture 0.
        glBindTexture(GL_TEXTURE_2D, texture->_textureID);
    }
    if (texture->_num == 1) {
        glActiveTexture(GL_TEXTURE1); // Activate first texture unit... specularTexture 1.
        glBindTexture(GL_TEXTURE_2D, texture->_textureID);
    }
}

void Textures::setTexture(Texture *texture)
{
    this->_textures.push_back(texture);
}

void Textures::loadTexture(Texture *texture) {
    std::ifstream file(texture->_filename);

    if (file.fail()) {
        std::cerr << "Texture file not exists" << '\n';
        throw;
    }
    int width, heigth, channels;
    unsigned char* pixels = stbi_load(texture->_filename.c_str(), &width, &heigth, &channels, 0);

    glGenTextures(1, &texture->_textureID);
    glBindTexture(GL_TEXTURE_2D, texture->_textureID); // all upcoming GL_TEXTURE_2D operations now have

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
