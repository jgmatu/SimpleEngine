#include "Engine.hpp"

Engine::Engine()
{
    _clock = Clock::getInstance();
    _keyboard = Keyboard::getInstance();
    _mouse = Mouse::getInstance();
}

Engine::Engine(Scene *scene) :
    Engine::Engine()
{

    _scene = scene;
}

Engine::~Engine()
{
    delete _scene;
    delete _keyboard;
    delete _clock;
    delete _mouse;
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
    glfwSetKeyCallback(_window, Keyboard::CallBackCharacters);

    // Cursor pos input...
    glfwSetCursorPosCallback(_window, Mouse::CursorPositionCallback);
    glfwSetMouseButtonCallback(_window, Mouse::MouseButtonCallback);

    GLFWcursor *cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
    if (!cursor) {
        std::cerr << "Error creating cursor ...." << '\n';
        throw;
    }
    glfwSetCursor(_window, cursor);
    glfwSetCursorEnterCallback(_window, Mouse::CursorEnterAreaCallback);

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
        _scene->init();
    } catch (std::exception &ex) {
        std::cerr << "Error init Engine... " << ex.what() << '\n';
        throw ex;
    } catch (...) {
        std::cout << "Fatal error init Engine " << '\n';
        throw;
    }
}

void Engine::update()
{
    _scene->update();
    _scene->draw();
}

void Engine::mainLoop() {
    do {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        update(); // ... Update Scene ...

        glfwSwapBuffers(_window); // Swap the color buffers.
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_INTERVAL_TIME_MS));
    } while(!glfwWindowShouldClose(_window));
    glfwTerminate();
}
