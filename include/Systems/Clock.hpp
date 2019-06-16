#ifndef CLOCK_H
#define CLOCK_H

#include <GLFW/glfw3.h>

class Clock {

public:
    Clock()
    {
        ;
    }

    void update()
    {
        ts = glfwGetTime();
    }


private:

    double ts;
};

#endif
