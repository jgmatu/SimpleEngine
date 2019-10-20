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
        std::cerr << "Failed to create program id" << '\n';
        throw ProgramException("Failed to create program id");
    }
    this->createVertexShader();
    this->createFragmentShader();
    this->link();
}

void Program::update(Uniforms *uniforms) {
    std::vector<std::string> names;

    names = uniforms->getUniformsNamesInt();
    for (uint32_t i = 0; i < names.size(); ++i) {
        if (_uniforms.find(names[i]) == _uniforms.end()) {
            this->createUniform(names[i]);
        } else {
            this->setUniform(names[i], uniforms->getUniformValueInt(names[i]));
        }
    }

    names = uniforms->getUniformsNamesFloat();
    for (uint32_t i = 0; i < names.size(); ++i) {
        if (_uniforms.find(names[i]) == _uniforms.end()) {
            this->createUniform(names[i]);
        } else {
            this->setUniform(names[i], uniforms->getUniformValueFloat(names[i]));
        }
    }

    names = uniforms->getUniformsNamesVec4();
    for (uint32_t i = 0; i < names.size(); ++i) {
        if (_uniforms.find(names[i]) == _uniforms.end()) {
            this->createUniform(names[i]);
        } else {
            this->setUniform(names[i], uniforms->getUniformValueVec4(names[i]));
        }
    }

    names = uniforms->getUniformsNamesVec3();
    for (uint32_t i = 0; i < names.size(); ++i) {
        if (_uniforms.find(names[i]) == _uniforms.end()) {
            this->createUniform(names[i]);
        } else {
            this->setUniform(names[i], uniforms->getUniformValueVec3(names[i]));
        }
    }

    names = uniforms->getUniformsNamesMat4();
    for (uint32_t i = 0; i < names.size(); ++i) {
        if (_uniforms.find(names[i]) == _uniforms.end()) {
            this->createUniform(names[i]);
        } else {
            this->setUniform(names[i], uniforms->getUniformValueMat4(names[i]));
        }
    }
}

void Program::use() {
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
        throw ProgramException("Fail opening file...");
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
        std::cerr << "Could not find uniform to create: " << uniformName << " " << err << '\n';
        throw ProgramException("Could not find uniform to create: " + uniformName + " " + err);
    }
    _uniforms.insert(std::pair<std::string, int>(uniformName, uniformLocation));
}

void Program::setUniform(std::string name, int value) {
    if (_uniforms.find(name) == _uniforms.end()) {
        createUniform(name);
    }
    glUniform1i(_uniforms[name], value);
}

void Program::setUniform(std::string name, float value) {
    if (_uniforms.find(name) == _uniforms.end()) {
        createUniform(name);
    }
    glUniform1f(_uniforms[name], value);
}

void Program::setUniform(std::string name, glm::vec4 value) {
    if (_uniforms.find(name) == _uniforms.end()) {
        createUniform(name);
    }
    glUniform4f(_uniforms[name], value.x, value.y, value.z, value.a);
}

void Program::setUniform(std::string name, glm::vec3 value) {
    if (_uniforms.find(name) == _uniforms.end()) {
        createUniform(name);
    }
    glUniform3f(_uniforms[name], value.x, value.y, value.z);
}

void Program::setUniform(std::string name, glm::mat4 value) {
    if (_uniforms.find(name) == _uniforms.end()) {
        createUniform(name);
    }
    glUniformMatrix4fv(_uniforms[name], 1, GL_FALSE,  glm::value_ptr(value));
}

int Program::createShader(const std::string& sc, int shaderType) {
    int params;
    const char* _sc = sc.c_str();
    int size = sc.size();

    int shaderId = glCreateShader(shaderType);
    if (shaderId == 0) {
        std::cerr << "Program error : " << "Error creating shader. Type: " << shaderType << '\n';
        throw ProgramException("Error creating shader. Type: " + shaderType);
    }
    glShaderSource(shaderId, 1, &_sc, &size);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &params);

    int InfoLogLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        char VertexShaderErrorMessage[InfoLogLength + 1];
        glGetShaderInfoLog(shaderId, InfoLogLength, NULL, VertexShaderErrorMessage);
        throw ProgramException(std::string("Shader Error Message: " + std::string(VertexShaderErrorMessage) + '\n'));
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
        sprintf(inflog, "Error linking shader code: %s\n", inflog);
        std::cerr << "Error linking shader : " << inflog << '\n';
        throw ProgramException("Error linking shader code:" + std::string(inflog));
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
        sprintf(inflog, "Error linking shader code: %s\n", inflog);
        std::cerr << "Error linking shader code : " << inflog << '\n';
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
