#ifndef CLOCK_H
#define CLOCK_H

#include <GLFW/glfw3.h>

class Clock {

public:

    static Clock* getInstance()
    {
        static Clock *instance;

        if (!instance) {
            instance = new Clock();
        }
        return instance;
    }

    ~Clock()
    {
        std::cout << "Delete clock :)" << '\n';
    }

    double now()
    {
        return glfwGetTime();
    }

private:

    Clock()
    {
        std::cout << "Create clock! :)" << '\n';
    };

};

#endif
