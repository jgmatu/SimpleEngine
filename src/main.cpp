#include <iostream>
#include <exception>

#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameObjects/GameObject.hpp"
#include "Components/Camera.hpp"
#include "Components/Material.hpp"
#include "Components/SkyBox.hpp"

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

    void update()
    {
        if (Keyboard::instance->isKeyPressed("c")) {
            _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), 0.01);
            _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), 0.01);
        }

        if (Keyboard::instance->isKeyPressed("k")) {
            Light *ligth = _gObject->getLigth("p0");
            ligth->setIntense(0.0);
            ligth->setPosition(glm::vec3(0.3f));

            ligth = _gObject->getLigth("p1");
            ligth->setIntense(0.0);

            ligth = _gObject->getLigth("p2");
            ligth->setIntense(0.0);

            ligth = _gObject->getLigth("p3");
            ligth->setIntense(0.0);
        }

        if (Keyboard::instance->isKeyPressed("l")) {
            Light *ligth = _gObject->getLigth("p0");
            ligth->setIntense(1.0);

            ligth = _gObject->getLigth("p1");
            ligth->setIntense(1.0);

            ligth = _gObject->getLigth("p2");
            ligth->setIntense(1.0);

            ligth = _gObject->getLigth("p3");
            ligth->setIntense(1.0);
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

GameObject *getCube(std::string name)
{
    GameObject *cube = new GameObject(name);

    std::string id_mesh = "cube_mesh";
    Cube *geometry_cube = new Cube(id_mesh);

    Material *material = new Material(new Model(geometry_cube->getMesh()));
    material->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    Texture *diffuse = new Texture("container2.png", "texture_diffuse");
    material->setTexture(id_mesh, diffuse);

    Texture *specular = new Texture("container2_specular.png", "texture_specular");
    material->setTexture(id_mesh, specular);

    cube->addComponent(material);

    return cube;
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
        scene->setLigth(points[i]);
    }
    //    this->setLigth(new Specular(glm::vec3(0.7, 0.7, 0.7), 0.078125));
    //    this->setLigth(new Spot(glm::vec3(1.0f, 1.0f, -2.0f), glm::vec3(0.0f, 0.0f, 1.0), 2.5, 7.5));
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
