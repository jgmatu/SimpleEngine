#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include <string>

#include "Components/Component.hpp"

class SkyBox : public Component {

public:

    SkyBox();
    ~SkyBox();

    // Este método SOLO se llama una vez la primera vez que se crea el componente.
    void start();

    // Método que se llama cada vez que el Componente se activa.
    void awakeStart();

    // Método que realiza transformaciones, cálculos de cosas.
    void update();

private:

    std::vector<std::string> faces;
    unsigned textureID;

    unsigned SkyBox::loadCubemap()
};


#endif // SKYBOX_H
