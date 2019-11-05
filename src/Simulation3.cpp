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


class CubeMove : public Component {

public:

    CubeMove()
    {
        ;
    }

    ~CubeMove()
    {
        ;
    }

    void start()
    {
        _gObject->translate(glm::vec3(0.0, 0.0, -5.0));
        _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), 0.5);
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

class FloorShadow : public Component {

public:

    FloorShadow()
    {
        ;
    }

    ~FloorShadow()
    {
     }

    void start()
    {
        _gObject->translate(glm::vec3(0.0, 0.0, -5.0));
        _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), 0.1);
//        _gObject->translate(glm::vec3(0.0, -0.5, -5.0));
//        _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), -1.5);
//        _gObject->scale(glm::vec3(10.0, 10.0, 10.0));
    }

    void update()
    {
        _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), 0.01);
    }

    void awakeStart()
    {
        ;
    }
};

GameObject* getSimpleCube(std::string name)
{
    GameObject *cube = new GameObject(name);
//    Cube *simple_cube = new Cube(name);

    Material *material = new Material();
    material->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    Texture *diffuse = new Texture("container2.png", "texture_diffuse");
    material->setTexture(name, diffuse);

    Texture *specular = new Texture("container2_specular.png", "texture_specular");
    material->setTexture(name, specular);

    Render *render = new Render();
    render->setMaterial(material);
    render->setModel(new Model("../models/cube/cube.obj"));

    cube->addDrawer(render);
    cube->addComponent(new CubeMove());
    return cube;
}

GameObject* getFloorToShadows(std::string name)
{
    GameObject* floor = new GameObject(name);

    Material *material = new Material();
    material->setProgram(new Program("../glsl/wall_vs.glsl", "../glsl/wall_fs.glsl"));

    Render *render = new Render();

    render->setModel(new Model("../models/wall/plane.obj"));
    render->setMaterial(material);

    floor->addDrawer(render);
    floor->addComponent(new FloorShadow());

    return floor;
}

GameObject* getNormalMoon(std::string name)
{
    GameObject* moon = new GameObject(name);

    Material *material = new Material();
    material->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    Render *render = new Render();

    render->setModel(new Model("../models/earth/sphere.obj"));
    render->setMaterial(material);

    moon->addDrawer(render);
    moon->addComponent(new Earth());

    return moon;
}

void addSimpleLigth(Scene *scene)
{
    Directional *d = new Directional("d");
    d->setIntense(1.0);
    d->setDirection(glm::vec3(-1.0, -1.0, -1.0));
//    d->setDirection(glm::vec3(0.0, 0.0, -1.0));
    scene->addLigth(d);
}

Scene* sceneSimulation3()
{
    Scene *scene = new Scene();

    addSimpleLigth(scene);

//    GameObject *cube1 = getSimpleCube("cube1");

//    GameObject *cube2 = getCube("cube2");
//    cube2->addComponent(new ExampleMove());

//    scene->addChild(cube1);
//    cube1->addChild(cube2);

//    GameObject *sphere = getBasicSphere("basic");
//    sphere->addComponent(new ChangeColor());

//    GameObject *glass = getGlass("glass");
//    glass->addComponent(new Glass());

//    scene->addChild(glass);

    scene->addChild(getNormalMoon("moon"));

    return scene;
}
