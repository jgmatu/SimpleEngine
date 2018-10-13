#include "Program/Program.hpp"

Program::Program(std::string vshader, std::string fshader) :
    _vshader(vshader),
    _fshader(fshader)
{
    std::cout << "Create program : " << _vshader << " " << _fshader << '\n';
}

Program::~Program() {
    std::cout << "Destroy program... " << '\n';
}

void Program::active() {
    this->createVertexShader();
    this->createFragmentShader();
    this->link();
}

void Program::render() {
    this->bind();
}

void Program::createVertexShader() {
    std::cout << "Create vertex shader: " << _vshader << '\n';
}

void Program::createFragmentShader() {
    std::cout << "Crete fragments shader: " << _fshader << '\n';
}

void Program::link() {
    std::cout << "Link program: " << _programId << '\n';
}

void Program::bind() {
    std::cout << "Bind program:" << _programId << '\n';
}


void Program::unbind() {
    std::cout << "Unbind program: " << _programId << '\n';
}

void Program::cleanup() {
    std::cout << "Clean up" << '\n';
}

void Program::createUniform(std::string uniformName) {
    std::cout << "Create uniform :" << uniformName << '\n';
}

//    void setUniform(std::string name, glm::vec3 value);
//    void setUniform(std::string name, glm::mat4 value);

void Program::setUniform(std::string name, int value) {
    std::cout << "Set uniform : " << name << " " << value << '\n';
}

std::string Program::getDataFile(const std::string& filename) {
    return "Program File data";
}

int Program::createShader(const std::string& sc, int shaderType) {
    std::cout << "Create Shader type..." << '\n';
    return 0;
}
