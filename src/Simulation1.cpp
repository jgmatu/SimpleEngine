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


class Example : public Component {

public:

    Example()
    {
        ;
    }

    ~Example()
    {

    }

    void start()
    {
        _gObject->translate(glm::vec3(0.0, 0.0, -5.0));
    }

    void powerOff()
    {
        std::vector<Light*> ligths = _gObject->getLigths();

        for (uint32_t i = 0; i < ligths.size(); ++i) {
            if (!ligths[i]->isLigth("s") && !ligths[i]->isLigth("d")) {
                ligths[i]->setIntense(0.0);
            }
        }
    }

    void powerOn()
    {
        std::vector<Light*> ligths = _gObject->getLigths();

        for (uint32_t i = 0; i < ligths.size(); ++i) {
            ligths[i]->setIntense(1.0);
        }
    }

    void update()
    {
        if (Keyboard::instance->isKeyPressed("c")) {
            _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), 0.01);
            _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), 0.01);
        }
        float distance = _gObject->distance("cube2");

        if (distance > 2.0f) {
            powerOn();
        } else {
            powerOff();
        }
    }

    void awakeStart()
    {
        ;
    }

};

class ExampleMove : public Component {

public:

    uint32_t counter;

    ExampleMove()
    {
        counter = 0;
    }

    ~ExampleMove()
    {

    }

    void start()
    {
        _gObject->translate(glm::vec3(5.0, 0.0, -1.0));
    }

    void update()
    {
        if (Keyboard::instance->isKeyPressed("a")) {
            _gObject->translate(glm::vec3(-0.1, 0.0, 0.0));
        }
        if (Keyboard::instance->isKeyPressed("d")) {
            _gObject->translate(glm::vec3(0.1, 0.0, 0.0));
        }

        if (_gObject->distance("cube1") < 2.0) {
            std::cout << "Event near cubes: " << counter++ << '\n';
        }
    }

    void awakeStart()
    {
        ;
    }

};

class Nanosuit : public Component {

public:

    Nanosuit()
    {
        ;
    }

    ~Nanosuit()
    {

    }

    void start()
    {
        _gObject->translate(glm::vec3(0.0, 0.3, 0.0));
        _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), 2.0);
    }

    void update()
    {
        ;
    }

    void awakeStart()
    {
        ;
    }

};

class ChangeColor : public Component {

public:

    ChangeColor()
    {
        ;
    }

    ~ChangeColor()
    {
        ;
    }

    void start()
    {
        _gObject->translate(glm::vec3(5.0, 0.0, -5.0));
        _gObject->setColor(glm::vec3(0.0, 0.0, 1.0));
    }

    void update()
    {
        if (Keyboard::instance->isKeyPressed("f")) {
            _gObject->setColor(glm::vec3(1.0, 0.0, 0.0));
        } else {
            _gObject->setColor(glm::vec3(0.0, 0.0, 1.0));
        }
    }

    void awakeStart()
    {
        ;
    }
};

class Glass : public Component {
public:

    Glass()
    {
        ;
    }

    ~Glass()
    {
        ;
    }

    void start()
    {
        _gObject->translate(glm::vec3(3.0, 0.5, -5.0));
    }

    void update()
    {
        ;
    }

    void awakeStart()
    {
        ;
    }
};

class Floor : public Component {
public:

    Floor()
    {
        ;
    }

    ~Floor()
    {
        ;
    }

    void start()
    {
        _gObject->translate(glm::vec3(0.0, -0.5, -5.0));
        _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), -1.5);
        _gObject->scale(glm::vec3(10.0, 10.0, 10.0));
    }

    void update()
    {
        ;
    }

    void awakeStart()
    {
        ;
    }
};

GameObject* getCube(std::string name)
{
    GameObject *cube = new GameObject(name);
    Model *plane = new Model("../models/Rubix/model/obj/RubixCube.obj");

    Material *material = new Material();
    material->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    Render *render = new Render();
    render->setMaterial(material);
    render->setModel(plane);

    cube->addDrawer(render);
    return cube;
}

GameObject* getBasicSphere(std::string name)
{
    GameObject *sphere = new GameObject(name);
    Sphere *sphere_basic = new Sphere(name);

    Material *material = new Material();
    material->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    Render *render = new Render();

    render->setMaterial(material);
    render->setModel(new Model(sphere_basic->getMesh()));

    sphere->addDrawer(render);
    return sphere;
}

GameObject* getPlaneToShadows(std::string name)
{
    GameObject* floor = new GameObject(name);
    Plane *plane = new Plane(name);

    Material *material = new Material();
    material->setProgram(new Program("../glsl/wall_vs.glsl", "../glsl/wall_fs.glsl"));

    Texture *diffuse = new Texture("brickwall.jpg", "texture_diffuse");
    Texture *specular = new Texture("brickwall.jpg", "texture_specular");
    Texture *normal = new Texture("brickwall_normal.jpg", "texture_normal");

    material->setTexture(name, diffuse);
    material->setTexture(name, specular);
    material->setTexture(name, normal);

    Render *render = new Render();

    render->setMaterial(material);
    render->setModel(new Model(plane->getMesh()));

    floor->addDrawer(render);
    floor->addComponent(new Floor());

    return floor;
}


GameObject* getGlass(std::string name)
{
    GameObject* glass = new GameObject(name);
    Plane *plane = new Plane(name);

    Material *material = new Material();
    material->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));
    material->setTransparent();

    Texture *diffuse = new Texture("blending_transparent_window.png", "texture_diffuse");
    Texture *specular = new Texture("blending_transparent_window.png", "texture_specular");

    material->setTexture(name, diffuse);
    material->setTexture(name, specular);

    Render *render = new Render();

    render->setMaterial(material);
    render->setModel(new Model(plane->getMesh()));

    glass->addDrawer(render);

    return glass;
}

std::vector<Light*> getLigthPoints()
{
    std::vector<glm::vec3> point_positions = {
        glm::vec3(3.0, 1.0, 3.0),
        glm::vec3(-2.0,  1.0,  1.0),
        glm::vec3(-1.0,  2.0,  3.0),
        glm::vec3( 0.0, -2.0,  0.0)
    };

    std::vector<Light*> points;
    for (uint32_t i = 0; i < point_positions.size(); ++i) {
        Point *p = new Point("p" + std::to_string(i));
        p->setPosition(point_positions[i]);
        p->setDistance();
        p->setIntense(1.0f);
        points.push_back(p);
    }
    return points;
}

void addLigths(Scene *scene)
{
    Directional *d = new Directional("d");
    d->setIntense(1.0);
    d->setDirection(glm::vec3(-1.0, -1.0, -1.0));
//    d->setDirection(glm::vec3(0.0, 0.0, -1.0));
    scene->addLigth(d);
}

Scene* sceneSimulation1()
{
    Scene *scene = new Scene();

    addLigths(scene);

    GameObject *cube1 = getCube("cube1");
    cube1->addComponent(new Nanosuit());

//    GameObject *cube2 = getCube("cube2");
//    cube2->addComponent(new ExampleMove());

    scene->addChild(cube1);
//    cube1->addChild(cube2);

//    GameObject *sphere = getBasicSphere("basic");
//    sphere->addComponent(new ChangeColor());

//    GameObject *glass = getGlass("glass");
//    glass->addComponent(new Glass());

//    scene->addChild(glass);

    scene->addChild(getPlaneToShadows("plane"));

    return scene;
}
