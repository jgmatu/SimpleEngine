#include "Engine.hpp"

Engine::Engine() :
    _systems()
{
    _scene = new Scene(0, "********************* SCENE *********************** ");
}

Engine::Engine(ObjectFactory *objectFactory) :
    Engine::Engine()
{
    for (unsigned i = 0; i < objectFactory->size(); ++i) {
        this->add(objectFactory->getGameObject(i));
    }
}

Engine::~Engine() {
    for (unsigned i = 0; i < _systems.size(); ++i) {
        delete _systems[i];
    }
    delete _scene;
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
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
}

void Engine::init() {
    std::cout << "Iniciar Engine!!" << '\n';
    try {
        this->initWindow();
        for (unsigned i = 0; i < _systems.size(); ++i) {
            _systems[i]->init(_scene);
        }
    } catch (std::exception &ex) {
        std::cerr << "Error init engine " << ex.what() << '\n';
        throw ex;
    } catch (...) {
        std::cout << "Fatal error init Engine " << '\n';
        throw;
    }
}

void Engine::add(System *sys) {
    _systems.push_back(sys);
}

void Engine::add(GameObject *gameObject) {
    _scene->addGameObject(gameObject);
}

void Engine::update(float dt) {
    for (unsigned i = 0; i < _systems.size(); ++i) {
        _systems[i]->update(dt, _scene);
    }
}

void Engine::mainLoop() {
    std::cout << "********************** MAIN LOOP ***************************************" << '\n';

    GameObject *sun = _scene->getGameObject(1);
    GameObject *earth = _scene->getGameObject(2);
    GameObject *moon = _scene->getGameObject(3);
    GameObject *mars = _scene->getGameObject(4);
    GameObject *mercury = _scene->getGameObject(5);
    GameObject *jupiter = _scene->getGameObject(6);

    // Lo tienes traslada el objeto desde la escena como pivote Hay que pivotar!!
    std::cout << *(this->_scene) << '\n';
    std::cout << *sun << '\n';
    std::cout << *earth << '\n';
    std::cout << *moon << '\n';
    std::cout << *mars << '\n';

    sun->addTexture("../resources/sun.png");
    earth->addTexture("../resources/earth_diffuse.jpg");
    moon->addTexture("../resources/moon.png");
    mars->addTexture("../resources/mars.png");
    mercury->addTexture("../resources/mercury.jpg");
    jupiter->addTexture("../resources/jupiter.jpg");

    glEnable(GL_DEPTH_TEST);
    do {
        float angle = std::fmod(glfwGetTime(), (2.0f * M_PI));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        sun->translate(glm::vec3(0.0f, 0.0f, -5.0f));

        earth->rotate(glm::vec3(0.0f, -5.0f, 0.0f), angle);
        earth->translate(glm::vec3(5.0f, 0.0f, 0.0f));
        earth->rotate(glm::vec3(0.0f, -5.0f, 0.0f), angle);
        earth->scale(glm::vec3(0.35f, 0.35f, 0.35f));

        moon->rotate(glm::vec3(0.0f, -5.0f, 0.0f), angle);
        moon->translate(2.0f * glm::vec3(1.0f, 0.0, 0.0f));
        moon->rotate(glm::vec3(0.0f, -5.0f, 0.0f), angle);
        moon->scale(glm::vec3(0.35f, 0.35f, 0.35f));

        mars->rotate(glm::vec3(0.0f, -5.0f, 0.0f), angle);
        mars->translate(glm::vec3(5.5f, 0.0f, 5.5f));
        mars->rotate(glm::vec3(0.0f, -5.0f, 0.0f), angle);
        mars->scale(glm::vec3(0.40f, 0.40f, 0.40f));

        mercury->rotate(glm::vec3(0.0f, -5.0f, 0.0f), angle);
        mercury->translate(glm::vec3(1.0f, 0.0f, 1.0f));
        mercury->rotate(glm::vec3(0.0f, -5.0f, 0.0f), angle);
        mercury->scale(glm::vec3(0.15f, 0.15f, 0.15f));

        jupiter->rotate(glm::vec3(0.0f, -3.0f, 0.0f), angle);
        jupiter->translate(glm::vec3(7.0f, 0.0f, -7.0f));
        jupiter->rotate(glm::vec3(0.0f, -5.0f, 0.0f), angle);
        jupiter->scale(glm::vec3(0.85f, 0.85f, 0.85f));

        this->update(0);

        glfwSwapBuffers(_window); // swap the color buffers.

        // Lo tienes traslada el objeto desde la escena como pivote Hay que pivotar!!
        std::cout << *(this->_scene) << '\n';
        std::cout << *sun << '\n';
        std::cout << *earth << '\n';
        std::cout << *moon << '\n';

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    } while(!glfwWindowShouldClose(_window));
    glfwTerminate();
}
