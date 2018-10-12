#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <iostream>
#include <map>

class Program {

public:

    Program(std::string vshader, std::string fshader);
    ~Program();

    void createVertexShader();
    void createFragmentShader();
    void link();

    void bind();
    void unbind();
    void cleanup();

    void createUniform(std::string uniformName);
//    void setUniform(std::string name, glm::vec3 value);
//    void setUniform(std::string name, glm::mat4 value);
    void setUniform(std::string name, int value);

private:

    std::string getDataFile(const std::string& filename);
    int createShader(const std::string& sc, int shaderType);

    unsigned _programId;
    unsigned _vertexShaderId;
    unsigned _fragmentShaderId;

    std::string _vshader;
    std::string _fshader;

    std::map<std::string, int> _uniforms;
};

#endif
