#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <iostream>
#include <map>

class Program {

public:

    Program();
    ~Program();

    void createUniform(std::string uniformName);
//    void setUniform(std::string name, glm::vec3 value);
//    void setUniform(std::string name, glm::mat4 value);
    void setUniform(std::string name, int value);

private:

    unsigned _programId;

    std::string _vshader;
    std::string _fshader;

    std::map<std::string, int> _uniforms;

};

#endif
