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
            p[i] = true;
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

    void update()
    {
        _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), 0.01);
        bool isPressed[NUM_POINTS];

        for (uint32_t i = 0; i < NUM_POINTS; ++i) {
            isPressed[i] = Keyboard::getInstance()->isKeyPressed(std::to_string(i + 1));

            if (isPressed[i] && !wasPresssed[i]) {
                conmute(i);
            }
            wasPresssed[i] = isPressed[i];
        }
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

GameObject *generateCube(std::string id)
{
    Cube* cubeData = new Cube(id); 
    Render *cubeRender = new Render();
    Material *cubeMaterial = new Material();

    cubeMaterial->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));
    cubeMaterial->setTexture(id, new Texture("../resources/container2.png", "texture_diffuse0"));
    cubeMaterial->setTexture(id, new Texture("../resources/container2_specular.png", "texture_specular0"));
    cubeRender->setMaterial(cubeMaterial);
    cubeRender->setModel(new Model(cubeData->getMesh()));

    GameObject *cube = new GameObject(id);
    cube->addDrawer(cubeRender);
    return cube;
}

Scene* MoveBoxesSim()
{
    Scene *sim = new Scene();
    GameObject *cube1 = generateCube("cube1");
    GameObject *cube2 = generateCube("cube2");

    cube1->addComponent(new Cube1());
    sim->addLigths(getSceneLigths());
    sim->addChild(cube1);

    return sim;
}