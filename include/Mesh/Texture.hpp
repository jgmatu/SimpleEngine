#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>

class Texture {

public:

     Texture();
     Texture(int num, std::string name, std::string filename);
    ~Texture();

    std::string _name;
    int _num;

    std::string _filename;
    GLuint _textureID;

};
#endif // TEXTURE_H
