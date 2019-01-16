#include "Engine.hpp"

Engine::Engine() :
    _systems()
{
    _scene = new Scene(0, "********************* SCENE *********************** ");
}

Camera *_cameraEvent;
Scene *_sceneEvent;

Engine::Engine(ObjectFactory *objectFactory) :
    Engine::Engine()
{
    for (unsigned i = 0; i < objectFactory->size(); ++i) {
        this->add(objectFactory->getGameObject(i));
    }
    _sceneEvent = this->_scene;
    _cameraEvent = _sceneEvent->_cameras[_sceneEvent->_camera];
}

Engine::~Engine() {
    for (unsigned i = 0; i < _systems.size(); ++i) {
        delete _systems[i];
    }
    delete _scene;
}

static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_UP) {
        _cameraEvent->_tf->_model = glm::translate(_cameraEvent->_tf->_model, glm::vec3(0.0, 0.0, 0.1));
    }
    if (key == GLFW_KEY_DOWN) {
        _cameraEvent->_tf->_model = glm::translate(_cameraEvent->_tf->_model, glm::vec3(0.0, 0.0, -0.1));
    }
    if (key == GLFW_KEY_LEFT) {
        _cameraEvent->_tf->_model = glm::translate(_cameraEvent->_tf->_model, glm::vec3(0.01, 0.0, 0.0));
    }
    if (key == GLFW_KEY_RIGHT) {
        _cameraEvent->_tf->_model = glm::translate(_cameraEvent->_tf->_model, glm::vec3(-0.01, 0.0, 0.0));
    }
    if (key == GLFW_KEY_Q) {
        _cameraEvent->_tf->_model = glm::rotate(_cameraEvent->_tf->_model, 0.01f, glm::vec3(-1.0f, 0.0f, 0.0f));
    }
    if (key == GLFW_KEY_E) {
        _cameraEvent->_tf->_model = glm::rotate(_cameraEvent->_tf->_model, 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        _sceneEvent->_camera = (_sceneEvent->_camera + 1) % _sceneEvent->MAX_CAMERAS;
        _cameraEvent = _sceneEvent->_cameras[_sceneEvent->_camera];
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

    // Depth buffer-z...
    glEnable(GL_DEPTH_TEST);

    // Stencil buffer...
    glEnable(GL_STENCIL_TEST);

    // Enabling transparency...
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    // Perfomance Culling draw...
//    glEnable(GL_CULL_F1ACE);
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

void Engine::genFrameBuffer()
{
    unsigned fbo;

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Error bindinig new frame buffer...." << '\n';
        return;
    }
    unsigned texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &fbo);
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
    std::vector<glm::vec3> vegetation_position = {
        glm::vec3(-1.5f,  0.0f, -0.48f),
        glm::vec3( 1.5f,  0.0f,  0.51f),
        glm::vec3( 0.0f,  0.0f,  0.7f),
        glm::vec3(-0.3f,  0.0f, -2.3f),
        glm::vec3( 0.5f,  0.0f, -0.6f)
    };

    std::vector<GameObject*> cubes(2);
    for (unsigned i = 0; i < 2; ++i) {
        cubes[i] = _scene->getGameObject(i + 1);
    }
    _scene->_cameras[0]->setGameObject(_scene);

    std::vector<glm::vec3> cube_positions = {
        glm::vec3(-1.0f,  0.0f, -0.99f),
        glm::vec3( 2.0f,  0.0f,  0.00f)
    };

//    GameObject *nanosuit = _scene->getGameObject(30);
//    _scene->_cameras[1]->setGameObject(nanosuit);
//    GameObject *_floor = _scene->getGameObject(0);
    std::vector<GameObject*> vegetation(vegetation_position.size());
    for (unsigned i = 0; i < vegetation.size(); ++i) {
        vegetation[i] = _scene->getGameObject(111 + i);
    }
    do {
//        float angle = std::fmod(glfwGetTime(), 2.0f * M_PI);
        glfwPollEvents();

//        nanosuit->rotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
//        nanosuit->scale(glm::vec3(0.05, 0.05, 0.05));
//        nanosuit->translate(glm::vec3(0.0, -12.0, -10.0));
        for (unsigned i = 0; i < vegetation_position.size(); ++i) {
            vegetation[i]->translate(vegetation_position[i]);
        }
        for (unsigned i = 0; i < cubes.size(); ++i) {
            cubes[i]->translate(cube_positions[i]);
        }
//        glm::vec3 lightPos = glm::vec3(0, 0, 10.0);

//        for (unsigned i = 0; i < points.size(); ++i) {
//            points[i]->translate(positions[i]);
//            points[i]->scale(glm::vec3(0.05, 0.05, 0.05));
//        }

//        for (unsigned i = 0; i < 5; ++i) {
//            Component *component = cubes[i]->getComponent(TypeComp::MATERIAL);

//            if (Material *material = dynamic_cast<Material*>(component)) {
//                material->eraseLigth(CompLigth::SCENE);
//                material->setLigth(new LightScene(lightPos));
//                glm::vec3 lightColor;
//                lightColor.x = sin(glfwGetTime() * 2.0f);
//                lightColor.y = sin(glfwGetTime() * 0.7f);
//                lightColor.z = sin(glfwGetTime() * 1.3f);
//                material->setColor(lightColor);
//            }
//        }
        this->update(0);
        glfwSwapBuffers(_window); // swap the color buffers.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    } while(!glfwWindowShouldClose(_window));
    glfwTerminate();
}
