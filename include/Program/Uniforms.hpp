#ifndef DATA_H
#define DATA_H

#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Uniforms {

public:

    Uniforms();
    ~Uniforms();

    void setUniformInt(std::string name, int value);
    void setUniformFloat(std::string name, float value);
    void setUniformVec3(std::string name, glm::vec3 value);
    void setUniformMat4(std::string name, glm::mat4 value);

    std::vector<std::string> getUniformsNamesInt();
    std::vector<std::string> getUniformsNamesFloat();
    std::vector<std::string> getUniformsNamesVec3();
    std::vector<std::string> getUniformsNamesMat4();

    glm::mat4 getUniformValueMat4(std::string name);
    glm::vec3 getUniformValueVec3(std::string name);
    int getUniformValueInt(std::string name);
    float getUniformValueFloat(std::string name);

private:

    std::map<std::string, int> _uniformsInt;
    std::map<std::string, float> _uniformsFloat;
    std::map<std::string, glm::vec3> _uniformsVec3;
    std::map<std::string, glm::mat4> _uniformsMat4;

};
#endif