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
        _gObject->scale(glm::vec3(0.10, 0.10, 0.10));
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
        _gObject->rotate(glm::vec3(0.0, -1.0, 0.0), std::fmod(angle += 0.01, (2.0f * M_PI)));
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
        _gObject->scale(glm::vec3(0.12, 0.12, 0.12));
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
        _gObject->scale(glm::vec3(0.50, 0.50, 0.50));
        _gObject->rotate(glm::vec3(0.0, -1.0, 0.0), std::fmod(angle += 0.08, (2.0f * M_PI)));
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
        _gObject->rotate(glm::vec3(0.0, -1.0, 0.0), std::fmod(angle += 0.01, (2.0f * M_PI)));
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

class SaturnAux : public Component {
private:
    float angle;

public:
    SaturnAux()
    {
        ;
    }

    void update()
    {
        _gObject->rotate(glm::vec3(0.0, -1.0, 0.0), std::fmod(angle += 0.01, (2.0f * M_PI)));
        _gObject->translate(glm::vec3(14.0, 0.0, 26.53));
    }
};

class Saturn : public Component {
private:
    float angle;

public:
    Saturn()
    {
        angle = 0;
    }

    void update()
    {
        _gObject->scale(glm::vec3(0.40, 0.40, 0.40));
//        _gObject->rotate(glm::vec3(0.0, -1.0, 0.0), std::fmod(angle += 0.05, (2.0f * M_PI)));
    }
};

class SaturnRing : public Component {

private:
    float angle;

public:

    SaturnRing()
    {
        angle = 0;
    }

    void start()
    {
        ;
    }

    void update()
    {
//        _gObject->rotate(glm::vec3(1.0, 1.0, 0.0), std::fmod(angle += 0.005, (M_PI / 12.0f)));
        _gObject->rotate(glm::vec3(1.0, 1.0, 0.0), M_PI / 12.0f);
    }
};

class Stars : public Component {

public:
    Stars()
    {
        ;
    }

    void update()
    {
        _gObject->scale(glm::vec3(100.0, 100.0, 100.0));
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

    model->setTransparentModel();
    render->setProgram(new Program("../glsl/user/clouds_vs.glsl", "../glsl/user/clouds_fs.glsl", isFile));
    render->setModel(model);
    clouds->addDrawer(render);
    return clouds;
}

GameObject *getRing(std::string path, std::string id)
{
    GameObject *ring = new GameObject(id);
    Model *model = new Model(path);
    Render *render = new Render();
    bool isFile = true;

    render->setProgram(new Program("../glsl/user/ring_vs.glsl", "../glsl/user/ring_fs.glsl", isFile));
    render->setModel(model);
    ring->addDrawer(render);
    return ring;
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

    SkyBox *skybox = new SkyBox(std::vector<std::string>({"../skybox/ame_nebula/right.tga", 
    "../skybox/ame_nebula/front.tga", "../skybox/ame_nebula/bottom.tga", 
    "../skybox/ame_nebula/back.tga", "../skybox/ame_nebula/top.tga", 
    "../skybox/ame_nebula/left.tga"}));

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
    skybox->addComponent(new Stars());

    // Add mercury
    GameObject *mercuryAux = new GameObject("mercuryAux");
    GameObject *mercury = getPlanet("../models/mercury/sphere.obj", "mercury");

    mercuryAux->addComponent(new MercuryAux());
    mercuryAux->addComponent(new Camera());
    mercury->addComponent(new Mercury());
    mercuryAux->addChild(mercury);

    // Add venus
    GameObject *venuxAux = new GameObject("venusAux");
    GameObject *venus = getPlanet("../models/venus/sphere.obj", "venus");

    venuxAux->addComponent(new VenusAux());
    venuxAux->addComponent(new Camera());
    venus->addComponent(new Venus());
    venuxAux->addChild(venus);

    // Add Earth
    GameObject *clouds = getClouds("../models/clouds/sphere.obj", "clouds");
    GameObject *cloudsAux = new GameObject("cloudsAux");

    cloudsAux->addComponent(new EarthAux());
    clouds->addComponent(new Clouds());
    cloudsAux->addChild(clouds);

    GameObject *earth = getPlanet("../models/earth/sphere.obj", "earth");
    GameObject* earthAux = new GameObject("earthAux");
    
    earthAux->addComponent(new EarthAux());
    earthAux->addComponent(new Camera());
    earth->addComponent(new Earth());
    earthAux->addChild(earth);

    // Add moon
    GameObject *moonAux = new GameObject("moonAux");
    GameObject *moon = getPlanet("../models/moon/sphere.obj", "moon");

    moonAux->addComponent(new MoonAux());
    moonAux->addComponent(new Camera());
    moon->addComponent(new Moon());

    // Add moon to the Earth
    moonAux->addChild(moon);
    earthAux->addChild(moonAux);

    // Add mars
    GameObject *marsAux = new GameObject("marsAux");
    GameObject *mars = getPlanet("../models/mars/sphere.obj", "mars");

    marsAux->addComponent(new MarsAux());
    marsAux->addComponent(new Camera());
    mars->addComponent(new Mars());
    marsAux->addChild(mars);

    // Add Jupiter
    GameObject *jupiterAux = new GameObject("jupiterAux");
    GameObject *jupiter = getPlanet("../models/jupiter/sphere.obj", "jupiter");

    jupiterAux->addComponent(new JupiterAux());
    jupiterAux->addComponent(new Camera());
    jupiter->addComponent(new Jupiter());
    jupiterAux->addChild(jupiter);

    // Add Saturn
    GameObject *saturnAux = new GameObject("saturnAux");
    GameObject *saturn = getPlanet("../models/saturn/sphere.obj", "saturn");
    GameObject *saturnRing = getRing("../models/saturn/saturn_ring.obj", "saturnRing");

    saturnAux->addComponent(new SaturnAux());
    saturnAux->addComponent(new Camera());
    saturn->addComponent(new Saturn());
    saturnRing->addComponent(new SaturnRing());
    saturnAux->addChild(saturn);
    saturnAux->addChild(saturnRing);

    // Generate tree nodes...
    scene->addChild(skybox);
    scene->addChild(sun);
    scene->addChild(mercuryAux);
    scene->addChild(venuxAux);
    scene->addChild(cloudsAux);
    scene->addChild(earthAux);
    scene->addChild(marsAux);
    scene->addChild(jupiterAux);
    scene->addChild(saturnAux);
    return scene;
}