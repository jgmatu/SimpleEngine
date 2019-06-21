#ifndef CLOCK_H
#define CLOCK_H

#include <GLFW/glfw3.h>

class Clock {

public:

    inline static Clock *instance;

    static Clock* getInstance()
    {
        if (!Clock::instance) {
            Clock::instance = new Clock();
        }
        return Clock::instance;
    }

    ~Clock()
    {
        Clock::instance = nullptr;
    }

    static double now()
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
