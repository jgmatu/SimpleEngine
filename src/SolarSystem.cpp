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
        _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), std::fmod(angle += 0.01, (2.0f * M_PI)));
        _gObject->translate(glm::vec3(5.0, 0.0, 0.0));
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
        ;
    }

    void update()
    {
        ;
    }
};

std::vector<Light*> solarSystemIlumination()
{
    std::vector<Light*> ilumination;

    Directional *dir = new Directional("d");
    dir->setDirection(glm::vec3(-1.0, -0.5, 0.0));
    dir->setIntense(0.5);

    Point *p = new Point("p");
    p->setIntense(1.0);
    p->setDistance(3250);
    p->setPosition(glm::vec3(0.0, 0.0, 0.0));

    ilumination.push_back(dir);
    ilumination.push_back(p);
    return ilumination;
}

GameObject* getPlanet(std::string path, std::string id)
{
    GameObject *planet = new GameObject(id);
    Model *model = new Model(path);
    Render *render = new Render();
    bool isFile = true;

    render->setProgram(new Program("../glsl/user/sun_vs.glsl", "../glsl/user/sun_fs.glsl", isFile));
    render->setModel(model);
    planet->addDrawer(render);
    return planet;
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

    GameObject *sun = getPlanet("../models/sun/sphere.obj", "sun");
    GameObject *earth = getPlanet("../models/earth/sphere.obj", "earth");
    GameObject *skybox = getStars("stars");

    earth->addComponent(new EarthAux());

    scene->addChild(sun);
    scene->addChild(earth);
    scene->addChild(skybox);
    return scene;
}