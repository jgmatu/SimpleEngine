#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include <glad/glad.h>

class Texture {

public:

    Texture(std::string filename, std::string type);
    ~Texture();

    static uint32_t TextureFromFile(std::string directory, std::string filename);
    static uint32_t TextureCubeMap(std::vector<std::string> _faces);

    friend std::ostream& operator<<(std::ostream& os, const Texture& texture);

private:

    friend class Model;
    friend class Material;

    const std::string DEFAULT_PATH = "../resources";

    void activeTexture();

    uint32_t _id;
    std::string _type;
    std::string _filename;
    std::string _path;

};

#endif
