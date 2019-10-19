#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include <string>
#include <iostream>

#include "Drawers/Drawer.hpp"
#include "Components/Camera.hpp"

class SkyBox : public Component {

public:

    SkyBox();
    SkyBox(std::vector<std::string> faces, Program *program);
    ~SkyBox();

    void active();
    void draw();
    void setView(Camera *camera);

private:

    void setParameter(std::string name, glm::vec3 val);
    void setParameter(std::string name, glm::mat4 val);
    void setParameter(std::string name, int val);
    void setParameter(std::string name, float val);

    std::vector<std::string> _faces;

    // Active Buffer.
    GLuint _VAO , _VBO;

    unsigned _textureID;

    Camera *_camera;
    Program *_program;
    Uniforms *_uniforms;

};


#endif // SKYBOX_H
