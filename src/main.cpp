#include <iostream>
#include <exception>

#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameObjects/GameObject.hpp"
#include "Components/Camera.hpp"

#include "Components/SkyBox.hpp"

#include "Model/Material.hpp"

#include "Geometries/Cube.hpp"
#include "Geometries/Sphere.hpp"
#include "Geometries/Plane.hpp"

#include "Engine.hpp"

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
            if (!ligths[i]->isLigth("s")) {
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

class ChangeColor : public Component {

public:

    ChangeColor()
    {
        ;
    }

    ~ChangeColor()
    {

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

GameObject* getCube(std::string name)
{
    GameObject *cube = new GameObject(name);
    Cube *geometry_cube = new Cube(name);

    Material *material = new Material();
    material->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    Texture *diffuse = new Texture("container2.png", "texture_diffuse");
    material->setTexture(name, diffuse);

    Texture *specular = new Texture("container2_specular.png", "texture_specular");
    material->setTexture(name, specular);

    MeshRender *render = new MeshRender();
    render->setMaterial(material);
    render->setModel(new Model(geometry_cube->getMesh()));

    cube->addComponent(render);
    return cube;
}

GameObject* getBasicSphere(std::string name)
{
    GameObject *sphere = new GameObject(name);
    Sphere *basic = new Sphere(name);

    Material *material = new Material();
    material->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    MeshRender *render = new MeshRender();

    render->setMaterial(material);
    render->setModel(new Model(basic->getMesh()));

    sphere->addComponent(render);
    return sphere;
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
    std::vector<Light*> points = getLigthPoints();

    for (uint32_t i = 0; i < points.size(); ++i) {
        scene->addLigth(points[i]);
    }
    Spot *s = new Spot("s", 2.5, 7.5);

    s->setDistance();
    s->setIntense(1.0f);
    s->setPosition(glm::vec3(0, 0, 2.0f));
    s->setDirection(glm::vec3(0.0f, 0.0f, -1.0));

    scene->addLigth(s);

    //    this->setLigth(new Directional(glm::vec3(0.0, 0.0, 1.0)));
}

Scene* sceneSimulation()
{
    Scene *scene = new Scene();

    GameObject *cube1 = getCube("cube1");
    cube1->addComponent(new Example());

    GameObject *cube2 = getCube("cube2");
    cube2->addComponent(new ExampleMove());

    scene->addChild(cube1);
    cube1->addChild(cube2);

    GameObject *sphere = getBasicSphere("basic");
    sphere->addComponent(new ChangeColor());

    scene->addChild(sphere);

    addLigths(scene);
    return scene;
}

int main(int argc, char* argv[]) {
    Engine *engine = nullptr;

    try {
        Scene *scene = sceneSimulation();
        engine = new Engine(scene);
        engine->init();
        engine->mainLoop();
    } catch (std::exception &ex) {
        std::cerr << "Engine Error : " << ex.what() << '\n';
    } catch (...) {
        std::cerr << "Engine fatal!" << '\n';
    }
    if (engine) {
        delete engine;
    }
}
