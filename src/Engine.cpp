#include "Engine.hpp"

Keyboard *_keyboard;

Engine::Engine() :
    _systems()
{
    _scene = new Scene();
    _clock = new Clock();
    _keyboard = new Keyboard();
}

Engine::Engine(Scene *scene) :
    Engine::Engine()
{
    if (scene) {
        delete _scene;
    }
    _scene = scene;
}

Engine::~Engine()
{
    for (uint32_t i = 0; i < _systems.size(); ++i) {
        delete _systems[i];
    }
    delete _scene;
}

static void KeyboardCallBackSpecialsCharacters(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    const char* name = glfwGetKeyName(key, 0);
    if (name) {
        _keyboard->pressKey(std::string(name), action == GLFW_PRESS || action == GLFW_REPEAT);
    } else {
        _keyboard->pressKey(key, action == GLFW_PRESS || action == GLFW_REPEAT);
    }

    // Exit engine...
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void Engine::initWindow() {
    // Initialize GLFW. Most GLFW functions will not work before doing this.
    if (!glfwInit()) {
        throw;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    // Create the window
    _window = glfwCreateWindow(1024, 768, "Graphic Engine", nullptr, nullptr);
    if (_window == nullptr) {
        std::cerr << "Failed to create the GLFW System window" << std::endl;
        throw;
    }

    // Setup a key callback. It will be called every time a key is pressed, repeated or released.
    glfwSetKeyCallback(_window, KeyboardCallBackSpecialsCharacters);
    // Make the OpenGL context current.
    glfwMakeContextCurrent(_window);

    // Enable v-sync.
//    glfwSwapInterval(1);

    // Make the window visible.
    glfwShowWindow(_window);
    gladLoadGL();

    // Depth buffer-z... 24 bits...
    glEnable(GL_DEPTH_TEST);

    // Stencil buffer... 8 bits...
     glEnable(GL_STENCIL_TEST);

    // Enabling transparency...
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    // Perfomance Culling draw...
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
}

void Engine::init() {
    std::cout << "Iniciar Engine!!" << '\n';
    try {
        initWindow();
        for (unsigned i = 0; i < _systems.size(); ++i) {
            _systems[i]->init(_scene);
        }
    } catch (std::exception &ex) {
        std::cerr << "Error init Engine... " << ex.what() << '\n';
        throw ex;
    } catch (...) {
        std::cout << "Fatal error init Engine " << '\n';
        throw;
    }
}

void Engine::add(System *sys) {
    _systems.push_back(sys);
}

void Engine::update(float dt)
{
    _clock->update();
    _scene->update(_keyboard, _clock);
    _scene->draw();
}

void Engine::mainLoop() {
    do {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        update(0); // ... Update Scene ...

        glfwSwapBuffers(_window); // Swap the color buffers.
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_INTERVAL_TIME_MS));
    } while(!glfwWindowShouldClose(_window));
    glfwTerminate();
}
