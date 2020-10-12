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

class Cube2 : public Component {

private:

public:

    Cube2()
    {
        ;
    }

    void start()
    {
        _gObject->translate(glm::vec3(2.0, -0.5, 0.0));
    }

    void update() 
    {
        ;
    }

};

class Cube1 : public Component  {

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
        _gObject->translate(glm::vec3(0.0, -0.5, 0.0));
    }

    void update()
    {
        switchIntensePointLigths();
    }

    void switchIntensePointLigths()
    {
        bool isPressed[NUM_POINTS];

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

class Plane2 : public Component {

private:

    glm::vec3 ligth_position;

public:

    Plane2()
    {
        this->ligth_position = glm::vec3(1.0, 1.0, 0.0);
    }
    ~Plane2()
    {
        ;
    }

    void start()
    {
        _gObject->translate(glm::vec3(0.0, -1.0, 0.0));
        _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), M_PI / 2.0);
        _gObject->scale(glm::vec3(10.0, 10.0, 10.0));
    }

    void update()
    {
        moveLigth();
    }

    void moveLigth()
    {
        Light *point = _gObject->getLigth("p0");

        if (Keyboard::instance->isKeyPressed("w")) {
            this->ligth_position = this->ligth_position + glm::vec3(0.0, 0.0, 0.05);
            point->setPosition(this->ligth_position);
        }
        if (Keyboard::instance->isKeyPressed("s")) {
            this->ligth_position = this->ligth_position + glm::vec3(0.0, 0.0, -0.05);
            point->setPosition(this->ligth_position);
        }
        if (Keyboard::instance->isKeyPressed("a")) {
            this->ligth_position = this->ligth_position + glm::vec3(0.05, 0.0, 0.0);
            point->setPosition(this->ligth_position);
        }
        if (Keyboard::instance->isKeyPressed("d")) {
            this->ligth_position = this->ligth_position + glm::vec3(-0.05, 0.0, 0.00);
            point->setPosition(this->ligth_position);
        }
    }
};

class Window : public Component {

public:
    Window()
    {
        ;
    }

    void start()
    {
        _gObject->translate(glm::vec3(0.0, 0.0, 5.0));
        _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), M_PI);
        _gObject->scale(glm::vec3(1.0, 1.0, 1.0));
    }

    void update()
    {
        ;
    }
};

class Window2 : public Component {

public:
    Window2()
    {
        ;
    }

    void start()
    {
        _gObject->translate(glm::vec3(0.5, 0.0, 3.0));
        _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), M_PI);
        _gObject->scale(glm::vec3(1.0, 1.0, 1.0));
    }

    void update()
    {
        ;
    }
};

std::vector<Light*> getSceneLigths()
{
    std::vector<Light*> points(NUM_POINTS);

    std::vector<glm::vec3> positions = {
        glm::vec3(2.0, 2.0, 0.0),
        glm::vec3(0.0, 2.0, 2.0),
        glm::vec3(-2.0, 2.0, 0.0),
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

GameObject *generateWindow(std::string id)
{
    Plane* planeData = new Plane(id);
    Mesh* windowMesh = planeData->getMesh();

    Material *windowMaterial = new Material();
    windowMaterial->setTexture(id, new Texture("../resources/blending_transparent_window.png", "texture_diffuse0"));
    windowMaterial->setTexture(id, new Texture("../resources/blending_transparent_window.png", "texture_specular0"));
    windowMesh->setMaterial(windowMaterial);
    
    GameObject *transparent = new GameObject(id);
    Render *transparentRender = new Render();
    Model *model = new Model(windowMesh);
    bool isFile = true;

    model->setTransparentModel();
    transparentRender->setProgram(new Program("../glsl/user/window_vs.glsl", "../glsl/user/window_fs.glsl", isFile));
    transparentRender->setModel(model);

    transparent->addDrawer(transparentRender);
    return transparent;
}

GameObject *generatePlane(std::string id)
{
    GameObject *plane = new GameObject(id);
    Render *planeRender = new Render();
    Model *model = new Model("../models/floor/plane.obj");
    bool isFile = true;

    planeRender->setProgram(new Program(cube_vs, cube_fs, !isFile));
    planeRender->setModel(model);

    plane->addDrawer(planeRender);
    plane->addComponent(new Plane2());
    return plane;
}

Scene* MoveBoxesSim()
{
    Scene *scene = new Scene();
    GameObject *cube1 = generateCube("cube1");
    GameObject *cube2 = generateCube("cube2");
    GameObject *plane = generatePlane("plane");
    GameObject *w1 = generateWindow("w1");
    GameObject *w2 = generateWindow("w2");

    cube1->addComponent(new Cube1());
    cube2->addComponent(new Cube2());
    w1->addComponent(new Window());
    w2->addComponent(new Window2());

    scene->addLigths(getSceneLigths());
    scene->addChild(plane);
    scene->addChild(cube1);
    scene->addChild(cube2);

    scene->addChild(w1);
    scene->addChild(w2);

    return scene;
}