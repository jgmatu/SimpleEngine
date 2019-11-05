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

class Stars : public Component {

public:

    Stars()
    {
        ;
    }

    ~Stars()
    {
        ;
    }

    void start()
    {
        _gObject->scale(glm::vec3(20.0, 20.0, 20.0));
    }

    void update()
    {
//        std::cerr << "distance : " << _gObject->distance("earth") << '\n';
//        std::cerr << *_gObject << '\n';
    }

    void awakeStart()
    {
        ;
    }
};

class Sun : public Component {

public:

    Sun()
    {
        ;
    }

    ~Sun()
    {
        ;
    }

    void start()
    {
//        _gObject->scale(glm::vec3(0.001, 0.001, 0.001));
    }

    void update()
    {
//        std::cerr << "distance : " << _gObject->distance("earth") << '\n';
//        std::cerr << *_gObject << '\n';
    }

    void awakeStart()
    {
        ;
    }
};

class EarthAux : public Component {

private:

    float angle;

public:

    EarthAux()
    {
        angle = 0;
    }

    ~EarthAux()
    {
        ;
    }

    void start()
    {
        ;
    }

    void update()
    {
        _gObject->_tf->_model = _gObject->search("sun")->_tf->_gModel;
        _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), std::fmod(angle += 0.01, (2.0f * M_PI)));
        _gObject->translate(glm::vec3(5.0, 0.0, 0.0));
    }

    void awakeStart()
    {
        ;
    }
};

class Earth : public Component {

public:

    Earth()
    {
        ;
    }

    ~Earth()
    {
        ;
    }

    void start()
    {
        _gObject->scale(glm::vec3(0.25, 0.25, 0.25));
        _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), (2.0f * M_PI * 23.0f) / 360.0f);
//        _gObject->rotate(glm::vec3(0.0, 0.0, 1.0), 2.0f * M_PI);
    }

    void update()
    {
        _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), -0.01);
    }

    void awakeStart()
    {
        ;
    }
};

class MoonAux : public Component {

private:
    float angle;

public:

    MoonAux()
    {
        angle = 0;
    }

    ~MoonAux()
    {

    }

    void start()
    {
        ;
    }

    void update()
    {
        _gObject->_tf->_model = _gObject->search("sun")->_tf->_gModel;
        _gObject->rotate(glm::vec3(0.0, 1.0, 1.0), std::fmod(angle += 0.05, (2.0f * M_PI)));
        _gObject->translate(glm::vec3(1.0, 0.0, 0.0));
    }

    void awakeStart()
    {
        ;
    }

};

class Moon : public Component {

public:

    Moon()
    {
        ;
    }

    ~Moon()
    {
        ;
    }

    void start()
    {
        _gObject->scale(glm::vec3(0.10, 0.10, 0.10));
    }

    void update()
    {
        _gObject->rotate(glm::vec3(0.0, 0.0, 1.0), 0.05);
    }

    void awakeStart()
    {
        ;
    }
};

GameObject* getStars(std::string name)
{
    GameObject *stars = new GameObject(name);
    std::vector<std::string> faces = {
        "../skybox/ame_nebula/back.tga", "../skybox/ame_nebula/left.tga",
        "../skybox/ame_nebula/front.tga", "../skybox/ame_nebula/bottom.tga",
        "../skybox/ame_nebula/top.tga", "../skybox/ame_nebula/right.tga"
    };
    Program *program = new Program("../glsl/skybox_vs.glsl", "../glsl/skybox_fs.glsl");
    SkyBox *skybox = new SkyBox(faces, program);

    stars->addDrawer(skybox);
    stars->addComponent(new Stars());
    return stars;
}

GameObject *getEarthAux(std::string name)
{
    GameObject *earthAux = new GameObject(name);

    earthAux->addComponent(new EarthAux());
    return earthAux;
}

GameObject *getMoonAux(std::string name)
{
    GameObject *moonAux = new GameObject(name);

    moonAux->addComponent(new MoonAux());
    return moonAux;
}

GameObject* getEarth(std::string name)
{
    GameObject *earth = new GameObject(name);
    Model *earth_model = new Model("../models/earth/sphere.obj");

    Material *material = new Material();
    material->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    Render *render = new Render();
    render->setMaterial(material);
    render->setModel(earth_model);

    earth->addComponent(new Earth());
    earth->addDrawer(render);

    return earth;
}

GameObject* getSun(std::string name)
{
    GameObject *sun = new GameObject(name);

    Material *material = new Material();
    material->setProgram(new Program("../glsl/sun_vs.glsl", "../glsl/sun_fs.glsl"));

    Render *render = new Render();
    render->setMaterial(material);
    render->setModel(new Model("../models/sun/sphere.obj"));

    sun->addDrawer(render);
    sun->addComponent(new Sun());

    return sun;
}

/*
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
    sphere->addComponent(new Sun());
    return sphere;
}
*/

GameObject* getMoon(std::string name)
{
    GameObject *moon = new GameObject(name);
    Model *moon_model = new Model("../models/moon/sphere.obj");

    Material *material = new Material();
    material->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    Render *render = new Render();
    render->setMaterial(material);
    render->setModel(moon_model);

    moon->addComponent(new Moon());
    moon->addDrawer(render);

    return moon;
}

Light* sunLigth()
{
    Point *p = new Point("p1");
    p->setPosition(glm::vec3(0.0, 0.0, 0.0));
    p->setDistance();
    p->setIntense(1.0f);
    return p;
}

Light* ambientLigth()
{
    Directional *d = new Directional("d");
    d->setDirection(glm::vec3(0.0, 0.0, -1.0));
    d->setIntense(1.0f);
    return d;
}


Scene* sceneSimulation2()
{
    Scene *scene = new Scene();

    scene->addLigth(sunLigth());

    GameObject *earthAux = getEarthAux("earthAux");
    scene->addChild(earthAux);
    earthAux->addChild(getEarth("earth"));

    GameObject *moonAux = getMoonAux("moonAux");
    earthAux->addChild(moonAux);
    moonAux->addChild(getMoon("moon"));

    scene->addChild(getSun("sun"));
    scene->addChild(getStars("stars"));

    return scene;
}
