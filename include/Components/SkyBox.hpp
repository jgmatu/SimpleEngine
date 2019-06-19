#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include <string>
#include <iostream>

#include "Model/Mesh.hpp"

#include "Components/Component.hpp"
#include "Components/Camera.hpp"


class SkyBox : public Component {

public:

    SkyBox();
    SkyBox(std::vector<std::string> faces, Program *program);
    ~SkyBox();

    // Este método SOLO se llama una vez la primera vez que se crea el componente.
    void start();

    // Método que se llama cada vez que el Componente se activa.
    void awakeStart();

    // Método que realiza transformaciones, cálculos de cosas.
    void update(Clock *clock);

    void draw();
    void active();

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
