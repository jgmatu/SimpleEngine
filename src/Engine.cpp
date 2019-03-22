#include "Engine.hpp"

Camera *_cameraEvent;
Scene *_sceneEvent;

Engine::Engine() :
    _systems()
{
    _scene = new Scene(0, "********************* SCENE *********************** ");
}

Engine::Engine(ObjectFactory *objectFactory) :
    Engine::Engine()
{
    for (unsigned i = 0; i < objectFactory->size(); ++i) {
        this->_scene->addGameObjects(objectFactory->getGameObjects());
    }
    _sceneEvent = this->_scene;
    _cameraEvent = _sceneEvent->_cameras[_sceneEvent->_camera];
    std::cout << "Camera Event : " << _sceneEvent->_camera << '\n';
}

Engine::~Engine() {
    for (unsigned i = 0; i < _systems.size(); ++i) {
        delete _systems[i];
    }
    delete _scene;
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    std::cout << "**** Key Callback ****" << '\n';
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_UP) {
        _cameraEvent->_view->_model = glm::translate(_cameraEvent->_view->_model, glm::vec3(0.0, 0.0, 0.1));
    }
    if (key == GLFW_KEY_DOWN) {
        _cameraEvent->_view->_model = glm::translate(_cameraEvent->_view->_model, glm::vec3(0.0, 0.0, -0.1));
    }
    if (key == GLFW_KEY_LEFT) {
        _cameraEvent->_view->_model = glm::translate(_cameraEvent->_view->_model, glm::vec3(0.1, 0.0, 0.0));
    }
    if (key == GLFW_KEY_RIGHT) {
        _cameraEvent->_view->_model = glm::translate(_cameraEvent->_view->_model, glm::vec3(-0.1, 0.0, 0.0));
    }
    if (key == GLFW_KEY_Q) {
        _cameraEvent->_view->_model = glm::rotate(_cameraEvent->_view->_model, 0.01f, glm::vec3(-1.0f, 0.0f, 0.0f));
    }
    if (key == GLFW_KEY_E) {
        _cameraEvent->_view->_model = glm::rotate(_cameraEvent->_view->_model, 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        _sceneEvent->_camera = (_sceneEvent->_camera + 1) % 3;
        _cameraEvent = _sceneEvent->_cameras[_sceneEvent->_camera];
        std::cout << "Change Camera : " << _sceneEvent->_camera << " Size : " << _sceneEvent->_cameras.size() << '\n';
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
    _window = glfwCreateWindow(800, 600, "Graphic Engine", nullptr, nullptr);
    if (_window == nullptr) {
        std::cerr << "Failed to create the GLFW System window" << std::endl;
        throw;
    }

    // Setup a key callback. It will be called every time a key is pressed, repeated or released.
    glfwSetKeyCallback(_window, keyCallback);

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

void Engine::update(float dt) {
    for (unsigned i = 0; i < _systems.size(); ++i) {
        _systems[i]->update(dt, _scene);
    }
}

void Engine::mainLoop() {
    do {
        glfwPollEvents();
        this->update(0); // ... Draw Scene ...
        glfwSwapBuffers(_window); // Swap the color buffers.
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    } while(!glfwWindowShouldClose(_window));
    glfwTerminate();
}
