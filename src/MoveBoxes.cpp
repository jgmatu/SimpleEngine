#include <iostream>
#include <exception>

#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameObjects/GameObject.hpp"
#include "GameObjects/Scene.hpp"

#include "Components/Camera.hpp"

#include "Drawers/Skybox.hpp"
#include "Model/Material.hpp"

#include "Geometries/Cube.hpp"
#include "Geometries/Sphere.hpp"
#include "Geometries/Plane.hpp"

static const int NUM_POINTS = 3;


class Cube1 : public Component 
{

private:

    bool wasPresssed[NUM_POINTS];
    bool p[NUM_POINTS];

public:

    Cube1() 
    {
        for (uint32_t i = 0; i < NUM_POINTS; ++i) {
            p[i] = false;
            wasPresssed[i] = false;
        }
    }
    
    ~Cube1()
    {
        ;
    }

    void start()
    {
        _gObject->translate(glm::vec3(0.0, 0.0, 0.0));
        if (GameObject *cube2 = _gObject->search("cube2")) {
            cube2->translate(glm::vec3(2.0, 0.0, 0.0));
        }
    }

    void update()
    {
        bool isPressed[NUM_POINTS];
        _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), 0.01);

        for (uint32_t i = 0; i < NUM_POINTS; ++i) {
            isPressed[i] = Keyboard::getInstance()->isKeyPressed(std::to_string(i + 1));

            if (isPressed[i] && !wasPresssed[i]) {
                conmute(i);
            }
            wasPresssed[i] = isPressed[i];
        }
    }

    void conmute(int idx)
    {
        Light *point = _gObject->getLigth("p" + std::to_string(idx));
        if (p[idx]) {
            point->setIntense(1.0);
        } else {
            point->setIntense(0.0);
        }
        p[idx] = !p[idx];
    }
};

std::vector<Light*> getSceneLigths()
{
    std::vector<Light*> points(NUM_POINTS);

    std::vector<glm::vec3> positions = {
        glm::vec3(1.0, 1.0, 0.0),
        glm::vec3(0.0, 1.0, 1.0),
        glm::vec3(-1.0, 1.0, 0.0),
    };

    for (uint32_t i = 0; i < NUM_POINTS; ++i) {
        points[i] = new Point("p" + std::to_string(i));
        points[i]->setPosition(positions[i]);
        points[i]->setDistance(3250);
        points[i]->setIntense(1.0);
    }

    return points;
}

const std::string cube_vs = "\n\
out vec3 normal;\n\
out vec3 fragPos;\n\
out vec2 texCoord;\n\
\n\
void main()\n\
{\n\
    texCoord = aTexCoords;\n\
    normal = mat3(transpose(inverse(model))) * aNormal;\n\
    fragPos = vec3(model * vec4(aPos, 1.0));\n\
    gl_Position = projection * view * model * vec4(aPos, 1.0);\n\
}\n\
";

const std::string cube_fs = "\n\
in vec3 normal;\n\
in vec3 fragPos;\n\
in vec2 texCoord;\n\
\n\
void main()\n\
{\n\
    vec3 norm = normalize(normal);\n\
    vec3 viewDir = normalize(viewPos - fragPos);\n\
    vec4 result = vec4(0.0, 0.0, 0.0, 0.0);\n\
\n\
    // phase 2: Point lights\n\
    for (int i = 0; i < npoints; ++i) {\n\
        result += calcPointLight(points[i], material.texture_diffuse0, material.texture_specular0, texCoord, norm, fragPos, viewDir);\n\
    }\n\
    fragColor = result;\n\
}\n";

GameObject *generateCube(std::string id)
{
    bool isFile = true;

    // Generate cube primitives...
    Cube* cubeData = new Cube(id); 
    Mesh *meshCube = cubeData->getMesh();

    // Generate cube textures...
    Material *cubeMaterial = new Material();
    cubeMaterial->setTexture(id, new Texture("../resources/container2.png", "texture_diffuse0"));
    cubeMaterial->setTexture(id, new Texture("../resources/container2_specular.png", "texture_specular0"));
    meshCube->setMaterial(cubeMaterial);
    Model *cubeModel = new Model(meshCube);

    // Generate renderizable GameObject...
    Render *cubeRender = new Render();
    cubeRender->setModel(cubeModel);
    cubeRender->setProgram(new Program(cube_vs, cube_fs, !isFile));

    GameObject *cube = new GameObject(id);
    cube->addDrawer(cubeRender);
    return cube;
}

Scene* MoveBoxesSim()
{
    Scene *scene = new Scene();
    GameObject *cube1 = generateCube("cube1");
    GameObject *cube2 = generateCube("cube2");

    cube2->addComponent(new Cube1());
    cube1->addComponent(new Cube1());
    scene->addLigths(getSceneLigths());
    scene->addChild(cube1);
    scene->addChild(cube2);

    return scene;
}