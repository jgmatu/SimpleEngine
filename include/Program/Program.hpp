#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <exception>
#include <fstream>

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


struct ProgramException : public std::exception {
    std::string msg;

    ProgramException(const std::string& msg) {
        this->msg = msg;
    }

    const char * what () const throw () {
        return std::string("Program error: " + msg).c_str();
    }
};

class Program {

public:

    Program(std::string vshader, std::string fshader);
    ~Program();

    void active();
    void render();

    void createUniform(std::string uniformName);

    void setUniform(std::string name, glm::mat4 value);
    void setUniform(std::string name, glm::vec3 value);
    void setUniform(std::string name, int value);

private:

    void createVertexShader();
    void createFragmentShader();
    void link();

    void bind();
    void unbind();
    void cleanup();

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
