#include "Model/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string filename, std::string type) :
    _id(-1),
    _filename("?")
{
    this->_filename = filename;
    this->_type = type;
    this->_path = Texture::DEFAULT_PATH;
}

void Texture::activeTexture()
{
    this->_id = Texture::TextureFromFile(this->_path, this->_filename);
}

uint32_t Texture::TextureFromFile(std::string directory, std::string filename) {
    uint32_t textureID = -1;
    std::string path = directory + "/" + filename;

    std::ifstream file(path);
    if (file.fail()) {
        std::cerr << "Texture file not exists : " << path << '\n';
        throw;
    }
    int32_t width, heigth, channels;
    uint8_t *pixels = stbi_load(path.c_str(), &width, &heigth, &channels, 0);
    if (!pixels) {
        std::cerr << "Error Loading texture on memory..." << '\n';
        stbi_image_free(pixels);
        throw;
    }
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID); // all upcoming GL_TEXTURE_2D.

    // set the texture wrapping parameters.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    } else if (channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    return textureID;
}

uint32_t Texture::TextureCubeMap(std::vector<std::string> _faces) {
    uint32_t _textureID;
    int width, height, nrChannels;

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);

    for (unsigned int i = 0; i < _faces.size(); ++i) {
        unsigned char *data = stbi_load(_faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (!data) {
            std::cerr << "Cubemap texture failed to load at path: " << _faces[i] << std::endl;
            continue;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,  0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return _textureID;
}

std::ostream& operator<<(std::ostream& os, const Texture& texture)
{
    os << texture._id << " : " << texture._path + " / " + texture._filename;
    return os;
}
