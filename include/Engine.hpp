#ifndef ENGINE_H
#define ENGINE_H

#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <math.h>

#include "Systems/Keyboard.hpp"
#include "Systems/Clock.hpp"

#include "GameObjects/Scene.hpp"

class Engine {

public:

    Engine(Scene *scene);
    ~Engine();

    void init();
    void update();
    void mainLoop();

private:

    void initWindow();
    void genFrameBuffer();
    void genRenderBuffer();

    GLFWwindow *_window;
    Scene *_scene;

};

#endif // ENGINE_H
