#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <exception>
#include <fstream>

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Uniforms.hpp"

struct ProgramException : public std::exception {
    std::string _msg;

    ProgramException(const std::string& msg) {
        this->_msg = msg;
    }

    const char* what() const throw () {
        const int MAX_STR = 255;
        char *data = (char*) malloc(MAX_STR * sizeof(char));

        if (!data) {
            fprintf(stderr, "%s\n", strerror(errno));
            return NULL;
        }
        strncpy(data, std::string("Program error: " + _msg).c_str(), MAX_STR);
        sprintf(data, "%s", data);
        return data;
    }
};

class Program {

public:

    Program(std::string vshader, std::string fshader);
    ~Program();

    void active();
    void use();
    void cleanup();

    void update(Uniforms *uniforms);
    void createUniform(std::string uniformName);

    void setUniform(std::string name, glm::mat4 value);
    void setUniform(std::string name, glm::vec3 value);
    void setUniform(std::string name, int value);
    void setUniform(std::string name, float value);

private:

    void createVertexShader();
    void createFragmentShader();
    void link();

    void bind();
    void unbind();

    std::string getDataFile(const std::string& filename);
    int createShader(const std::string& sc, int shaderType);

    uint32_t _programId;
    uint32_t _vertexShaderId;
    uint32_t _fragmentShaderId;

    std::string _vshader;
    std::string _fshader;

    std::map<std::string, int> _uniforms;
};

#endif
