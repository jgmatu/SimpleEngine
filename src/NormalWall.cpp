#include <iostream>
#include <exception>

#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameObjects/GameObject.hpp"
#include "GameObjects/Scene.hpp"

#include "Components/Controller.hpp"
#include "Components/Camera.hpp"

#include "Drawers/Skybox.hpp"
#include "Model/Material.hpp"

#include "Geometries/Cube.hpp"
#include "Geometries/Sphere.hpp"
#include "Geometries/Plane.hpp"

class WallController : public Controller {

private:
    bool wasPressed;

public: 

    WallController()
    {
        wasPressed = false;
    }

    ~WallController()
    {
        ;
    }

    void start()
    {
        for (uint32_t i = 0; i < _cameras.size(); ++i) {
            _cameras[i]->translate(glm::vec3(0.0, 0.0, -5.0));
        }
    }

    void update()
    {
        bool isPressed = Keyboard::instance->isKeyPressed("k");
        if (!wasPressed && isPressed) {
            this->changeCamera();
        }
        wasPressed = isPressed;

        for (uint32_t i = 0; i < _cameras.size(); ++i) {
            if (Keyboard::instance->isKeyPressed(GLFW_KEY_DOWN)) {
                _cameras[i]->translate(glm::vec3(0, 0, 0.05));
            }
            if (Keyboard::instance->isKeyPressed(GLFW_KEY_LEFT)) {
                _cameras[i]->translate(glm::vec3(-0.05, 0, 0));
            }
            if (Keyboard::instance->isKeyPressed(GLFW_KEY_RIGHT)) {
                _cameras[i]->translate(glm::vec3(0.05, 0, 0));
            }
            if (Keyboard::instance->isKeyPressed(GLFW_KEY_UP)) {
                _cameras[i]->translate(glm::vec3(0, 0, -0.05));
            }
            if (Keyboard::instance->isKeyPressed("a")) {
                _cameras[i]->rotate(glm::vec3(0.0, 1.0, 0.0), 0.05);
            }
            if (Keyboard::instance->isKeyPressed("d")) {
                _cameras[i]->rotate(glm::vec3(0.0, 1.0, 0.0), -0.05);
            }
            if (Keyboard::instance->isKeyPressed("w")) {
                _cameras[i]->rotate(glm::vec3(1.0, 0.0, 0.0), 0.05);
            }
            if (Keyboard::instance->isKeyPressed("s")) {
                _cameras[i]->rotate(glm::vec3(1.0, 0.0, 0.0), -0.05);
            }
        }
    }
};

class Wall : public Component {

private:

    float angle;

public:

    Wall() 
    {
        angle = 0;
    }
    
    ~Wall()
    {
        ;
    }

    void start()
    {
        ;
    }

    void update() 
    {
        _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), std::fmod(angle += 0.01, (2.0f * M_PI)));
    }
};

const std::string vshader = "\
uniform vec3 lightPos;\n\
uniform vec3 viewPos;\n\
\n\
out vec3 normal;\n\
out vec3 fragPos;\n\
out vec2 texCoord;\n\
\n\
out vec3 TangentLightPos;\n\
out vec3 TangentViewPos;\n\
out vec3 TangentFragPos;\n\
\n\
void main()\n\
{\n\
    texCoord = aTexCoords;\n\
    fragPos = vec3(model * vec4(aPos, 1.0));\n\
    normal = mat3(transpose(inverse(model))) * aNormal;\n\
\n\
    mat3 TBN = getTBNMatrix(model);\n\
    TangentLightPos = TBN * lightPos;\n\
    TangentViewPos  = TBN * viewPos;\n\
    TangentFragPos  = TBN * fragPos;\n\
\n\
    gl_Position = projection * view * model * vec4(aPos, 1.0);\n\
}\n\
";

const std::string fshader = "\n\
\n\
in vec2 texCoord;\n\
in vec3 TangentLightPos;\n\
in vec3 TangentViewPos;\n\
in vec3 TangentFragPos;\n\
in vec3 normal;\n\
\n\
void main()\n\
{\n\
    vec3 norm = texture(material.texture_normal0, texCoord).rgb;\n\
    norm = normalize(norm * 2.0 - 1.0);\n\
//    norm = -normal;\n\
\n\
    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);\n\
    vec4 result = vec4(0.0, 0.0, 0.0, 0.0);\n\
\n\
    // phase 1: Directional lights\n\
    result += calcDirLight(directional, material.texture_diffuse0, material.texture_specular0, texCoord, norm, viewDir);\n\
    fragColor = result;\n\
}\n\
";

const std::string fpath = "../glsl/user/wall_fs.glsl";
const std::string vpath = "../glsl/user/wall_vs.glsl";

GameObject* getWall(std::string id)
{
    GameObject *wall = new GameObject(id);
    Render *wallRender = new Render();
    Model *model = new Model("../models/wall/plane.obj");
    bool isFile = true;

    wallRender->setProgram(new Program(vpath, fpath, isFile));
    wallRender->setModel(model);

    wall->addDrawer(wallRender);
    wall->addComponent(new Wall());
    return wall;
}

Light* getSunLigth()
{
    Directional *dir = new Directional("d1");

    dir->setDirection(glm::vec3(0.0, -0.5, -1.0));
    dir->setIntense(1.0);
    return dir;
}

Scene* NormalWallSim()
{
    Scene *scene = new Scene();

    scene->addChild(getWall("wall"));
    scene->addLigth(getSunLigth());
    scene->addController(new WallController());
    return scene;
}
