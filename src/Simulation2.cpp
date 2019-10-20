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

GameObject* getSun(std::string name)
{
    GameObject *sphere = new GameObject(name);
    Sphere *sphere_basic = new Sphere(name);

    Material *material = new Material();
    material->setProgram(new Program("../glsl/sun_vs.glsl", "../glsl/sun_fs.glsl"));

    Texture *diffuse = new Texture("sun.png", "texture_diffuse");
    Texture *specular = new Texture("sun.png", "texture_specular");

    material->setTexture(name, diffuse);
    material->setTexture(name, specular);

    Render *render = new Render();

    render->setMaterial(material);
    render->setModel(new Model(sphere_basic->getMesh()));

    sphere->addDrawer(render);
    return sphere;
}

Light *sunLigth()
{
    Point *p = new Point("p1");
    p->setPosition(glm::vec3(0.0, 0.0, 0.0));
    p->setDistance();
    p->setIntense(1.0f);
    return p;
}

Light *ambientLigth()
{
    Directional *d = new Directional("d");
    d->setDirection(glm::vec3(0.0, 0.0, -1.0));
    d->setIntense(1.0f);
    return d;
}


Scene* sceneSimulation2()
{
    Scene *scene = new Scene();

    scene->addLigth(ambientLigth());
    scene->addLigth(sunLigth());
    scene->addChild(getSun("sun"));

    return scene;
}
