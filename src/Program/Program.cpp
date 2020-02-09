#include "Program/Program.hpp"

Program::Program(std::string vshader, std::string fshader, bool isFile) :
    _vshader(vshader),
    _fshader(fshader)
{
    _programId = 0;
    _vertexShaderId = 0;
    _fragmentShaderId = 0;
    _isFile = isFile;
}

Program::~Program() {
    std::cout << "Destroy program... " << '\n';
}

void Program::active() {
    _programId = glCreateProgram();
    if (_programId == 0) {
        throw ProgramException("Failed to create program id : " + _programId);
    }
    std::cout << "**** ACTIVE PROGRAM ****" << std::endl;
    this->createVertexShader();
    this->createFragmentShader();
    this->link();
}

void Program::update(Uniforms *uniforms) {
    std::vector<std::string> names;

    names = uniforms->getUniformsNamesInt();
    for (uint32_t i = 0; i < names.size(); ++i) {
        this->setUniform(names[i], uniforms->getUniformValueInt(names[i]));
    }

    names = uniforms->getUniformsNamesFloat();
    for (uint32_t i = 0; i < names.size(); ++i) {
        this->setUniform(names[i], uniforms->getUniformValueFloat(names[i]));
    }

    names = uniforms->getUniformsNamesVec4();
    for (uint32_t i = 0; i < names.size(); ++i) {
        this->setUniform(names[i], uniforms->getUniformValueVec4(names[i]));
    }

    names = uniforms->getUniformsNamesVec3();
    for (uint32_t i = 0; i < names.size(); ++i) {
        this->setUniform(names[i], uniforms->getUniformValueVec3(names[i]));
    }

    names = uniforms->getUniformsNamesMat4();
    for (uint32_t i = 0; i < names.size(); ++i) {
        this->setUniform(names[i], uniforms->getUniformValueMat4(names[i]));
    }
}

void Program::use() {
    this->bind();
}

std::string Program::getFilesDefUtils(std::vector<std::string> files)
{
    std::string defUtils;

    for (uint32_t i = 0; i < files.size(); ++i) {
        defUtils += getDataFile(files[i]) + '\n';
    }
    return defUtils;
}

std::string Program::getProgramDefinition(const std::string& program, uint16_t type) {
    switch (type) {
    case GL_VERTEX_SHADER:
        return getFilesDefUtils(_utilsVertexFiles) + program;
    case GL_FRAGMENT_SHADER:
        return getFilesDefUtils(_utilsFragmentFiles) + program;
    default:
        std::cerr << "Undefined program type: " << __func__ << std::endl;
        throw;
    }
}

void Program::createUserUniform(uint32_t nline, std::string uniformLine)
{
    std::istringstream iss(uniformLine);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    if (results.size() != 3) {
        throw ProgramException(nline + ": Invalid uniform variable :" + uniformLine);
    }
    std::string type = results[1];
    std::string name = results[2];

    std::cout << "Type : " << type << std::endl;
    std::cout << "Name : " << name.substr(0, name.size()- 1) << std::endl;
}

void Program::createUserUniforms(std::string shaderCode)
{
    std::string line;
    std::istringstream stream(shaderCode);
    uint32_t nline = 0;

    while (std::getline(stream, line)) {
        if (std::regex_search(line, std::regex("^uniform") )) {
            createUserUniform(nline, line);
        }
        ++nline;
    }
}

void Program::createVertexShader() {
    std::string shaderCode = this->_vshader;

    if (_isFile) {
        shaderCode = getDataFile(this->_vshader);
    }
    std::cout << " **** VERTEX SHADER **** \n" << shaderCode << std::endl;
    _vertexShaderId = createShader(getProgramDefinition(shaderCode, GL_VERTEX_SHADER), GL_VERTEX_SHADER);
    createUserUniforms(shaderCode);
}

void Program::createFragmentShader() {
    std::string shaderCode = this->_fshader;

    if (_isFile) {
        shaderCode = getDataFile(this->_fshader);
    }
    std::cout << "**** FRAGMENTS SHADER ****\n" << shaderCode << std::endl;
    _fragmentShaderId = createShader(getProgramDefinition(shaderCode, GL_FRAGMENT_SHADER), GL_FRAGMENT_SHADER);
    createUserUniforms(shaderCode);
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

int Program::createShader(const std::string& shaderCode, uint16_t shaderType) {
    int params;
    const char* _sc = shaderCode.c_str();
    int size = shaderCode.size();
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
        char VertexShaderErrorMessage[InfoLogLength + 1];
        glGetShaderInfoLog(shaderId, InfoLogLength, NULL, VertexShaderErrorMessage);
        throw ProgramException(std::string("Shader Error Message: " + std::string(VertexShaderErrorMessage) + '\n'));
    }
    glAttachShader(_programId, shaderId);
    return shaderId;
}

void Program::link() {
    int params;
    char inflog[32 * 1024];
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
