#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <map>
#include <vector>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>

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
        const int MAX_STR = 32 * 1024;
        char *data = (char*) malloc(MAX_STR * sizeof(char));

        if (!data) {
            fprintf(stderr, "%s\n", strerror(errno));
            return NULL;
        }
        strncpy(data, std::string("Program error...\n " + _msg).c_str(), MAX_STR);
        return data;
    }
};

class Program {

public:

    Program(std::string vshader, std::string fshader, bool isFile);
    ~Program();

    void active();
    void use();
    void cleanup();

    void update(Uniforms *uniforms);
    void createUniform(std::string uniformName);

    void setUniform(std::string name, glm::mat4 value);
    void setUniform(std::string name, glm::vec3 value);
    void setUniform(std::string name, glm::vec4 value);
    void setUniform(std::string name, int value);
    void setUniform(std::string name, float value);

private:

    #define DEF_VS_HEADER_FILE "../glsl/utils/vs_h.glsl"
    #define DEF_TBN_FUNCT_FILE "../glsl/utils/tbn_function.glsl"

    inline static const std::vector<std::string> _utilsVertexFiles = {
        DEF_VS_HEADER_FILE,
        DEF_TBN_FUNCT_FILE,
    };

    #define DEF_FS_HEADER_FILE "../glsl/utils/fs_h.glsl"
    #define DEF_DIR_LIGTH_FILE "../glsl/utils/dir_light_func.glsl"
    #define DEF_POINT_LIGTH_FILE "../glsl/utils/point_light_func.glsl"
    #define DEF_SPOT_LIGTH_FILE "../glsl/utils/spot_light_func.glsl"
    #define DEF_DBG_DEPTH_FILE "../glsl/utils/deph_dbg.glsl"

    inline static const std::vector<std::string> _utilsFragmentFiles = {
        DEF_FS_HEADER_FILE,
        DEF_DIR_LIGTH_FILE,
        DEF_POINT_LIGTH_FILE,
        DEF_SPOT_LIGTH_FILE,
        DEF_DBG_DEPTH_FILE,
    };

    void createVertexShader();
    void createFragmentShader();
    void link();

    void bind();
    void unbind();

    std::string getFilesDefUtils(std::vector<std::string> files);
    std::string getProgramDefinition(const std::string& program, uint16_t type);

    void createUserUniform(uint32_t nline, std::string uniformLine);
    void createUserUniforms(std::string shaderCode);
    
    std::string getDataFile(const std::string& filename);
    int createShader(const std::string& sc, uint16_t shaderType);

    bool _isFile;

    uint32_t _programId;
    uint32_t _vertexShaderId;
    uint32_t _fragmentShaderId;

    std::string _vshader;
    std::string _fshader;

    // Primitive uniforms with name and id added on OpenGL context!
    std::map<std::string, int> _uniforms;
};

#endif
