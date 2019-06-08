#include "Program/Uniforms.hpp"

Uniforms::Uniforms()
{
    ;
}

Uniforms::~Uniforms()
{
    ;
}

void Uniforms::setUniformInt(std::string name, int value) {
    _uniformsInt[name] = value;
}

void Uniforms::setUniformFloat(std::string name, float value) {
    _uniformsFloat[name] = value;
}

void Uniforms::setUniformVec3(std::string name, glm::vec3 value) {
    _uniformsVec3[name] = value;
}

void Uniforms::setUniformMat4(std::string name, glm::mat4 value) {
    _uniformsMat4[name] = value;
}

std::vector<std::string> Uniforms::getUniformsNamesInt() {
    std::vector<std::string> names;

    for(std::map <std::string, int>::iterator it = _uniformsInt.begin(); it != _uniformsInt.end(); ++it) {
        names.push_back(it->first);
    }
    return names;
}

std::vector<std::string> Uniforms::getUniformsNamesFloat() {
    std::vector<std::string> names;

    for(std::map <std::string, float>::iterator it = _uniformsFloat.begin(); it != _uniformsFloat.end(); ++it) {
        names.push_back(it->first);
    }
    return names;
}

std::vector<std::string> Uniforms::getUniformsNamesMat4() {
    std::vector<std::string> names;

    for(std::map <std::string, glm::mat4>::iterator it = _uniformsMat4.begin(); it != _uniformsMat4.end(); ++it) {
        names.push_back(it->first);
    }
    return names;
}

std::vector<std::string> Uniforms::getUniformsNamesVec3() {
    std::vector<std::string> names;

    for(std::map <std::string, glm::vec3>::iterator it = _uniformsVec3.begin(); it != _uniformsVec3.end(); ++it) {
        names.push_back(it->first);
    }
    return names;
}

int Uniforms::getUniformValueInt(std::string name) {
    return _uniformsInt[name];
}

float Uniforms::getUniformValueFloat(std::string name) {
    return _uniformsFloat[name];
}

glm::vec3 Uniforms::getUniformValueVec3(std::string name) {
    return _uniformsVec3[name];
}

glm::mat4 Uniforms::getUniformValueMat4(std::string name) {
    return _uniformsMat4[name];
}
