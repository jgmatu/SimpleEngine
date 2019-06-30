#ifndef COMPONENT_H
#define COMPONENT_H

#include "Constants/TypeComp.hpp"

#include "Systems/Mouse.hpp"
#include "Systems/Keyboard.hpp"
#include "Systems/Clock.hpp"

class GameObject;

class Component {

public:

    virtual ~Component() {};

    // Este método SOLO se llama una vez la primera vez que se crea el componente.
    virtual void start() = 0;

    // Método que se llama cada vez que el Componente se activa.
    virtual void awakeStart() = 0;

    // Método que realiza transformaciones, cálculos de cosas.
    virtual void update() = 0;


protected:

    friend class GameObject;

    TypeComp _type;

    GameObject *_gObject;
};

#endif // COMPONENT_H
