#include "Engine.hpp"

Camera *_cameraEvent;
Scene *_sceneEvent;
Keyboard *_keyboard;

Engine::Engine() :
    _systems()
{
    _scene = new Scene();
}

Engine::Engine(Scene *scene) :
    _systems()
{
    _scene = scene;
    _sceneEvent = _scene;
    _keyboard = new Keyboard();
}

Engine::~Engine() {
    for (unsigned i = 0; i < _systems.size(); ++i) {
        delete _systems[i];
    }
    delete _scene;
}

static void KeyboardCallBackCharacters(GLFWwindow *window, unsigned int codepoint)
{
    char c = codepoint;
    std::cout << "**** Key Callback **** : [" << c << "]" << '\n';
    _keyboard->pressKey(std::string(&c));
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
    _window = glfwCreateWindow(800, 600, "Graphic Engine", nullptr, nullptr);
    if (_window == nullptr) {
        std::cerr << "Failed to create the GLFW System window" << std::endl;
        throw;
    }

    // Setup a key callback. It will be called every time a key is pressed, repeated or released.
    glfwSetCharCallback(_window, KeyboardCallBackCharacters);

    // Make the OpenGL context current.
    glfwMakeContextCurrent(_window);

    // Enable v-sync.
    glfwSwapInterval(1);

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
        this->initWindow();
        _scene->initCameras();
        for (unsigned i = 0; i < _systems.size(); ++i) {
            _systems[i]->init(_scene);
        }
        _cameraEvent = _sceneEvent->_cameras[_sceneEvent->_camera];
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

void Engine::update(float dt) {
    for (unsigned i = 0; i < _systems.size(); ++i) {
        _systems[i]->update(dt, _scene);
    }
}

void Engine::mainLoop() {
    do {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        this->update(0); // ... Draw Scene ...
        glfwSwapBuffers(_window); // Swap the color buffers.
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_INTERVAL_TIME_MS));
    } while(!glfwWindowShouldClose(_window));
    glfwTerminate();
}
