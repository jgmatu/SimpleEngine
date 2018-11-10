#include "Program/Program.hpp"

Program::Program(std::string vshader, std::string fshader) :
    _vshader(vshader),
    _fshader(fshader)
{
    _programId = 0;
    _vertexShaderId = 0;
    _fragmentShaderId = 0;
}

Program::~Program() {
    std::cout << "Destroy program... " << '\n';
}

void Program::active() {
    _programId = glCreateProgram();
    if (_programId == 0) {
        throw ProgramException("Failed to create program id");
    }
    this->createVertexShader();
    this->createFragmentShader();
    this->link();
}

void Program::render() {
    this->bind();
}

void Program::createVertexShader() {
    const std::string sc = getDataFile(this->_vshader);

    _vertexShaderId = createShader(sc, GL_VERTEX_SHADER);
}

void Program::createFragmentShader() {
    const std::string sc = getDataFile(this->_fshader);

    _fragmentShaderId = createShader(sc, GL_FRAGMENT_SHADER);
}

std::string Program::getDataFile(const std::string& filename) {
    std::ifstream file(filename);

    file.open("r");
    if (!file.is_open()) {
        throw ProgramException("Failing opening file...");
    }
    std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return data;
}

void Program::createUniform(std::string uniformName) {
    int uniformLocation = glGetUniformLocation(_programId, uniformName.c_str());

    if (uniformLocation < 0) {
        std::string err;
        if (uniformLocation == GL_INVALID_VALUE) {
            err += "Invalid value";
        }
        if (uniformLocation == GL_INVALID_OPERATION) {
            err += "Invalid operation";
        }
        throw ProgramException("Could not find uniform to create: " + uniformName + " " + err);
    }
    _uniforms.insert(std::pair<std::string, int>(uniformName, uniformLocation));
}


void Program::setUniform(std::string name, glm::vec3 value) {
    glUniform3f(_uniforms[name], value.x, value.y, value.z);
}

void Program::setUniform(std::string name, glm::mat4 value) {
    glUniformMatrix4fv(_uniforms[name], 1, GL_FALSE,  glm::value_ptr(value));
};

void Program::setUniform(std::string name, int value) {
    glUniform1i(_uniforms[name], value);
}

int Program::createShader(const std::string& sc, int shaderType) {
    int params;
    const char* _sc = sc.c_str();
    int size = sc.size();

    int shaderId = glCreateShader(shaderType);
    if (shaderId == 0) {
        throw ProgramException("Error creating shader. Type: " + shaderType);
    }

    glShaderSource(shaderId, 1, &_sc, &size);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &params);

    int InfoLogLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        throw ProgramException("Vertex Shader Error Message: " + VertexShaderErrorMessage[0] + '\n');
    }
    glAttachShader(_programId, shaderId);
    return shaderId;
}

void Program::link() {
    int params;
    char inflog[1024];
    int size;

    glLinkProgram(_programId);
    glGetProgramiv(_programId, GL_LINK_STATUS, &params);
    if (!params) {
        glGetProgramInfoLog(_programId, 1024, &size, inflog);
        sprintf(inflog, "Error linking Shader code: %s\n", inflog);
        throw ProgramException(std::string(inflog));
    }
    if (_vertexShaderId != 0) {
        glDetachShader(_programId, _vertexShaderId);
    }
    if (_fragmentShaderId != 0) {
        glDetachShader(_programId, _fragmentShaderId);
    }
    glValidateProgram(_programId);
    glGetProgramiv(_programId, GL_LINK_STATUS, &params);
    if (!params) {
        glGetProgramInfoLog(_programId, 1024, &size, inflog);
        sprintf(inflog, "Error linking Shader code: %s\n", inflog);
        throw ProgramException(std::string(inflog));
    }
}

void Program::bind() {
    glUseProgram(_programId);
}


void Program::unbind() {
    glUseProgram(0);
}

void Program::cleanup() {
    unbind();
    if (_programId != 0) {
        glDeleteProgram(_programId);
    }
}
