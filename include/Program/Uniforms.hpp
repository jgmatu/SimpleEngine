#ifndef DATA_H
#define DATA_H

#include <map>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Uniforms {

public:

    Uniforms();
    ~Uniforms();

    void update(Uniforms *uniforms);

    void setUniformInt(std::string name, int value);
    void setUniformFloat(std::string name, float value);
    void setUniformVec4(std::string name, glm::vec4 value);
    void setUniformVec3(std::string name, glm::vec3 value);
    void setUniformMat4(std::string name, glm::mat4 value);

    std::vector<std::string> getUniformsNamesInt();
    std::vector<std::string> getUniformsNamesFloat();
    std::vector<std::string> getUniformsNamesVec4();
    std::vector<std::string> getUniformsNamesVec3();
    std::vector<std::string> getUniformsNamesMat4();

    glm::mat4 getUniformValueMat4(std::string name);
    glm::vec3 getUniformValueVec3(std::string name);
    glm::vec4 getUniformValueVec4(std::string name);

    int getUniformValueInt(std::string name);
    float getUniformValueFloat(std::string name);

    friend std::ostream& operator<<(std::ostream& os, const Uniforms& uniforms);

private:

    std::map<std::string, int> _uniformsInt;
    std::map<std::string, float> _uniformsFloat;
    std::map<std::string, glm::vec3> _uniformsVec3;
    std::map<std::string, glm::vec4> _uniformsVec4;
    std::map<std::string, glm::mat4> _uniformsMat4;

};
#endif
