#ifndef ENGINE_H
#define ENGINE_H

#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <math.h>

#include "Systems/System.hpp"
#include "GameObjects/ObjectFactory.hpp"
#include "GameObjects/Scene.hpp"

class Engine {

public:

    Engine();
    Engine(ObjectFactory *objectFactory);
    ~Engine();

    void init();
    void update(float dt);
    void mainLoop();
    void add(System *sys);
    void add(GameObject *gameObject);

private:

    void initWindow();
    void genFrameBuffer();

    GLFWwindow *_window;

    std::vector<System*> _systems;
    Scene *_scene;
    Camera *_camera;

};

#endif // ENGINE_H
