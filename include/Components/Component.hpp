#ifndef COMPONENT_H
#define COMPONENT_H

#include "Systems/Mouse.hpp"
#include "Systems/Keyboard.hpp"
#include "Systems/Clock.hpp"

class GameObject;

class Component {

public:

    virtual ~Component() {};

    // Este método SOLO se llama una vez la primera vez que se crea el componente.
    virtual void start()
    {
        ;
    }

    // Método que realiza transformaciones, cálculos de cosas.
    virtual void update()
    {
        ;
    }

protected:

    friend class GameObject;
    GameObject *_gObject;

};

#endif // COMPONENT_H
