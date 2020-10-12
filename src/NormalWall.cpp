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

const std::vector<std::string> TUNNEL = {
    "w1", "w2", "w3", "w4", "w5", "w6", "w7", "w8", "w9",
    "w10", "w11", "w12", "w13", "w14", "w15", "w16", "w17", "w18"
};


class Wall : public Component {

private:

    struct Rotation {
        Rotation() : r(), a(0) {}
        Rotation(glm::vec3 rotation, float angle) :
            r(rotation), a(angle) {} 

        glm::vec3 r;
        float a;
    };

    const std::map<std::string, Rotation> wall_rotate = {
        {"w1", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w2", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w3", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w4", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w5", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w6", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w7", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w8", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w9", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w10", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w11", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w12", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w13", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w14", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w15", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w16", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w17", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
        {"w18", Rotation(glm::vec3(1.0, 0.0, 0.0), M_PI)},
    };

    const std::map<std::string, glm::vec3> wall_translate = {
        {"w1", glm::vec3(-8.0, 0.0, 0.0)},
        {"w2", glm::vec3(-7.0, 0.0, 0.0)},
        {"w3", glm::vec3(-6.0, 0.0, 0.0)},
        {"w4", glm::vec3(-5.0, 0.0, 0.0)},
        {"w5", glm::vec3(-4.0, 0.0, 0.0)},
        {"w6", glm::vec3(-3.0, 0.0, 0.0)},
        {"w7", glm::vec3(-2.0, 0.0, 0.0)},
        {"w8", glm::vec3(-1.0, 0.0, 0.0)},
        {"w9", glm::vec3( 0.0, 0.0, 0.0)},
        {"w10", glm::vec3(-8.0, 0.0, -1.0)},
        {"w11", glm::vec3(-7.0, 0.0, -1.0)},
        {"w12", glm::vec3(-6.0, 0.0, -1.0)},
        {"w13", glm::vec3(-5.0, 0.0, -1.0)},
        {"w14", glm::vec3(-4.0, 0.0, -1.0)},
        {"w15", glm::vec3(-3.0, 0.0, -1.0)},
        {"w16", glm::vec3(-2.0, 0.0, -1.0)},
        {"w17", glm::vec3(-1.0, 0.0, -1.0)},
        {"w18", glm::vec3( 0.0, 0.0, -1.0)},
    };

    std::string _id;
    float angle;

public:

    Wall(std::string id) 
    {
        angle = M_PI;
        this->_id = id;
    }
    
    ~Wall()
    {
        ;
    }

    void start()
    {
        // Translation each wall...
        GameObject *wall = _gObject->search(this->_id);
        std::map<std::string, glm::vec3>::const_iterator itTraslation;
     
        itTraslation = wall_translate.find(this->_id);

        wall->translate(itTraslation->second);

        // Rotation each wall...
        std::map<std::string, Rotation>::const_iterator itRotation;
        itRotation = wall_rotate.find(this->_id);

        wall->rotate(itRotation->second.r, itRotation->second.a);
    }

    void update() 
    {
        GameObject *wall = _gObject->search(this->_id);
         
        // Translate...
        std::map<std::string, glm::vec3>::const_iterator itTraslation;
        itTraslation = wall_translate.find(this->_id);
        wall->translate(itTraslation->second);

        // Rotate...
        if (Keyboard::instance->isKeyPressed("1")) {
            angle += 0.01;
        } 
        if (Keyboard::instance->isKeyPressed("2")) {
            angle -= 0.01;
        }
        wall->rotate(glm::vec3(1.0, 0.0, 0.0), std::fmod(angle, (2.0f * M_PI)));
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


GameObject* getWall(std::string id)
{
    GameObject *wall = new GameObject(id);
    Render *wallRender = new Render();
    Model *model = new Model("../models/wall/plane.obj");
    bool isFile = true;

    const std::string fpath = "../glsl/user/wall_fs.glsl";
    const std::string vpath = "../glsl/user/wall_vs.glsl";

    wallRender->setProgram(new Program(vpath, fpath, isFile));
    wallRender->setModel(model);

    wall->addDrawer(wallRender);
    wall->addComponent(new Wall(id));
    return wall;
}

Light* getSunLigth()
{
    Directional *dir = new Directional("d1");

    dir->setDirection(glm::vec3(0.0, -0.5, -1.0));
    dir->setIntense(1.0);
    return dir;
}

void generateTunel(Scene *scene)
{
    GameObject *wall = nullptr;

    for (uint32_t i = 0; i < TUNNEL.size(); ++i) {
        wall = getWall(TUNNEL[i]);
        wall->addComponent(new Wall(TUNNEL[i]));
        scene->addChild(wall);
    }
}

Scene* NormalWallSim()
{
    Scene *scene = new Scene();

    scene->addLigth(getSunLigth());
    generateTunel(scene);
    scene->addController(new WallController());
    return scene;
}
