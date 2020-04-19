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

class MercuryAux : public Component {
private:
    float angle;

public:
    MercuryAux()
    {
        angle = 0;
    }

    void update()
    {
        _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), std::fmod(angle += 0.01, (2.0f * M_PI)));
        _gObject->translate(glm::vec3(1.5, 0.0, 1.65));
    }
};

class Mercury : public Component {
private:
    float angle;
    
public:
    Mercury()
    {
        angle = 0;
    }

    void update()
    {
        _gObject->scale(glm::vec3(0.15, 0.15, 0.15));
        _gObject->rotate(glm::vec3(0.0, -1.0, 0.0), std::fmod(angle += 0.05, (2.0f * M_PI)));
    }
};

class VenusAux : public Component {
private:
    float angle;

public:

    VenusAux()
    {
        angle = 0;
    }

    void update()
    {
        _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), std::fmod(angle += 0.01, (2.0f * M_PI)));
        _gObject->translate(glm::vec3(3.5, 0.0, 0));
    }
};

class Venus : public Component {
private:
    float angle;

public:

    Venus()
    {
        angle = 0;
    }

    void update()
    {
        _gObject->scale(glm::vec3(0.20, 0.20, 0.20));
        _gObject->rotate(glm::vec3(0.0, -1.0, 0.0), std::fmod(angle += 0.05, (2.0f * M_PI)));
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

    void update()
    {
        _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), std::fmod(angle += 0.01, (2.0f * M_PI)));
        _gObject->translate(glm::vec3(7.5, 0.0, 6.61));
   }
};

class Clouds : public Component {
private:
    float angle;

public:
    Clouds()
    {
        angle = 0;
    }

    void update()
    {
        _gObject->scale(glm::vec3(0.51, 0.51, 0.51));
        _gObject->rotate(glm::vec3(0.0, -1.0, 0.0), std::fmod(angle += 0.05, (2.0f * M_PI)));
    }
};

class Earth : public Component {

private:
    float angle;

public:

    Earth()
    {
        angle = 0;
    }

    void update()
    {
        _gObject->scale(glm::vec3(0.50, 0.50, 0.50));
        _gObject->rotate(glm::vec3(0.0, -1.0, 0.0), std::fmod(angle += 0.05, (2.0f * M_PI)));
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

    void update()
    {
        _gObject->rotate(glm::vec3(0.0, 1.0, 1.0), std::fmod(angle += 0.01, (2.0f * M_PI)));
        _gObject->translate(glm::vec3(1.0, 0.0, 0.0));
    }
};

class Moon : public Component {

private:
    float angle;

public:
    Moon()
    {
        angle = 0;
    }

    void update()
    {
        _gObject->scale(glm::vec3(0.10, 0.10, 0.10));
        _gObject->rotate(glm::vec3(0.0, -1.0, 0.0), std::fmod(angle += 0.005, (2.0f * M_PI)));
    }
};

class MarsAux : public Component {
private:
    float angle;

public:
    MarsAux()
    {
        angle = 0;
    }

    void update()
    {
        _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), std::fmod(angle += 0.01, (2.0f * M_PI)));
        _gObject->translate(glm::vec3(10.9, 0.0, 5));
    }
};

class Mars : public Component {
private:
    float angle;
    
public:
    Mars()
    {
        angle = 0;
    }

    void update()
    {
        _gObject->scale(glm::vec3(0.50, 0.50, 0.50));
        _gObject->rotate(glm::vec3(0.0, -1.0, 0.0), std::fmod(angle += 0.05, (2.0f * M_PI)));
    }
};

class Jupiter : public Component {
private:
    float angle;

public:
    Jupiter()
    {
        angle = 0;
    }

    void update()
    {
        _gObject->scale(glm::vec3(0.80, 0.80, 0.80));
        _gObject->rotate(glm::vec3(0.0, -1.0, 0.0), std::fmod(angle += 0.05, (2.0f * M_PI)));
    }
};

class JupiterAux : public Component {
private:
    float angle;

public:

    JupiterAux()
    {
        angle = 0;
    }

    void update()
    {
        _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), std::fmod(angle += 0.01, (2.0f * M_PI)));
        _gObject->translate(glm::vec3(12.0, 0.0, 16.0));
    }
};

std::vector<Light*> solarSystemIlumination()
{
    std::vector<Light*> ilumination;

    Point *p = new Point("p");
    p->setIntense(1.0);
    p->setDistance(3250);
    p->setPosition(glm::vec3(0.0, 0.0, 0.0));

    ilumination.push_back(p);
    return ilumination;
}

GameObject* getPlanet(std::string path, std::string id)
{
    GameObject *planet = new GameObject(id);
    Model *model = new Model(path);
    Render *render = new Render();
    bool isFile = true;

    render->setProgram(new Program("../glsl/user/planet_vs.glsl", "../glsl/user/planet_fs.glsl", isFile));
    render->setModel(model);
    planet->addDrawer(render);
    return planet;
}

GameObject *getClouds(std::string path, std::string id)
{
    GameObject *clouds = new GameObject(id);
    Model *model = new Model(path);
    Render *render = new Render();
    bool isFile = true;

    render->setProgram(new Program("../glsl/user/clouds_vs.glsl", "../glsl/user/clouds_fs.glsl", isFile));
    model->setTransparentModel();
    render->setModel(model);
    clouds->addDrawer(render);
    return clouds;
}

GameObject* getSun(std::string path, std::string id)
{
    GameObject *sun = new GameObject(id);
    Model *model = new Model(path);
    Render *render = new Render();
    bool isFile = true;

    render->setProgram(new Program("../glsl/user/sun_vs.glsl", "../glsl/user/sun_fs.glsl", isFile));
    render->setModel(model);
    sun->addDrawer(render);
    sun->scale(glm::vec3(2.0, 2.0, 2.0));
    return sun;
}

GameObject *getStars(std::string id)
{
    GameObject *stars = new GameObject(id);

    SkyBox *skybox = new SkyBox(std::vector<std::string>({"../skybox/ame_nebula/left.tga", 
    "../skybox/ame_nebula/front.tga", "../skybox/ame_nebula/bottom.tga", 
    "../skybox/ame_nebula/back.tga", "../skybox/ame_nebula/top.tga", 
    "../skybox/ame_nebula/right.tga"}));

    stars->addDrawer(skybox);
    return stars;
}

Scene* SolarSystemSim()
{
    Scene *scene = new Scene();
    scene->addLigths(solarSystemIlumination());

    // Sun and Stars...
    GameObject *sun = getSun("../models/sun/sphere.obj", "sun");
    GameObject *skybox = getStars("stars");

    // Add mercury
    GameObject *mercuryAux = new GameObject("mercuryAux");
    GameObject *mercury = getPlanet("../models/mercury/sphere.obj", "mercury");

    mercuryAux->addComponent(new MercuryAux());
    mercury->addComponent(new Mercury());
    mercuryAux->addChild(mercury);

    // Add venus
    GameObject *venuxAux = new GameObject("venusAux");
    GameObject *venus = getPlanet("../models/venus/sphere.obj", "venus");

    venuxAux->addComponent(new VenusAux());
    venus->addComponent(new Venus());
    venuxAux->addChild(venus);

    // Add Earth
    GameObject *clouds = getClouds("../models/clouds/sphere.obj", "clouds");
    GameObject *cloudsAux = new GameObject("cloudsAux");

    cloudsAux->addComponent(new EarthAux());
    clouds->addComponent(new Clouds());
    cloudsAux->addChild(clouds);

    GameObject *earth = getPlanet("../models/earth/sphere.obj", "earth");
    GameObject* auxEarth = new GameObject("earthAux");
    
    auxEarth->addComponent(new EarthAux());
    earth->addComponent(new Earth());
    auxEarth->addChild(earth);

    // Add moon
    GameObject *moonAux = new GameObject("moonAux");
    GameObject *moon = getPlanet("../models/moon/sphere.obj", "moon");

    moonAux->addComponent(new MoonAux());
    moon->addComponent(new Moon());

    // Add moon to the Earth
    moonAux->addChild(moon);
    auxEarth->addChild(moonAux);

    // Add mars
    GameObject *marsAux = new GameObject("marsAux");
    GameObject *mars = getPlanet("../models/mars/sphere.obj", "mars");

    marsAux->addComponent(new MarsAux());
    mars->addComponent(new Mars());
    marsAux->addChild(mars);

    // Add Jupiter
    GameObject *jupiterAux = new GameObject("jupiterAux");
    GameObject *jupiter = getPlanet("../models/jupiter/sphere.obj", "jupiter");

    jupiterAux->addComponent(new JupiterAux());
    jupiter->addComponent(new Jupiter());
    jupiterAux->addChild(jupiter);

    // Generate tree nodes...
    scene->addChild(sun);
    scene->addChild(mercuryAux);
    scene->addChild(venuxAux);
    scene->addChild(cloudsAux);
    scene->addChild(auxEarth);
    scene->addChild(marsAux);
    scene->addChild(jupiterAux);
    scene->addChild(skybox);
    return scene;
}