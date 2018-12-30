#include "Mesh/Texture.hpp"

Texture::Texture()
{
    ;
}

Texture::Texture(int num, std::string name, std::string filename) :
    Texture::Texture()
{
    this->_num = num;
    this->_name = name;
    this->_filename = filename;
}

Texture::~Texture()
{
    ;
}
