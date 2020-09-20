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


const std::string SandVertexShader = "\
uniform vec3 lightPos;\n\
uniform vec3 viewPos;\n\
\n\
out vec3 normal;\n\
out vec3 fragPos;\n\
out vec2 texCoord;\n\
\n\
out vec3 TangentLightPos;\n\
out vec3 TangentViewPos;\n\
out vec3 TangentFragPos;\n\
\n\
void main()\n\
{\n\
    texCoord = aTexCoords;\n\
    fragPos = vec3(model * vec4(aPos, 1.0));\n\
    normal = mat3(transpose(inverse(model))) * aNormal;\n\
\n\
    mat3 TBN = getTBNMatrix(model);\n\
    TangentLightPos = TBN * lightPos;\n\
    TangentViewPos  = TBN * viewPos;\n\
    TangentFragPos  = TBN * fragPos;\n\
\n\
    gl_Position = projection * view * model * vec4(aPos, 1.0);\n\
}\n\
";

const std::string SandFragmentShader = "\n\
\n\
in vec2 texCoord;\n\
in vec3 TangentLightPos;\n\
in vec3 TangentViewPos;\n\
in vec3 TangentFragPos;\n\
in vec3 normal;\n\
\n\
void main()\n\
{\n\
    vec3 norm = texture(material.texture_normal0, texCoord).rgb;\n\
    norm = normalize(norm * 2.0 - 1.0);\n\
//    norm = -normal;\n\
\n\
    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);\n\
    vec4 result = vec4(0.0, 0.0, 0.0, 0.0);\n\
\n\
    // phase 1: Directional lights\n\
    result += calcDirLight(directional, material.texture_diffuse0, material.texture_specular0, texCoord, norm, viewDir);\n\
    fragColor = result;\n\
}\n\
";

const std::vector<std::string> AIRPLANES = {
    "a1", "a2", "a3", "a4", "a5", "a6"
};

class Sand : public Component {

public:

    Sand()
    {
        ;
    }

    void start()
    {
        _gObject->translate(glm::vec3(0.0, -1.0, 0.0));
        _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), M_PI / 2.0);
        _gObject->scale(glm::vec3(20.0, 20.0, 20.0));
    }

    void update()
    {
        ;
    }

};

class Road : public Component {

private:

public:

    Road()
    {
        ;
    }

    void start()
    {
        _gObject->translate(glm::vec3(0.0, -0.95, 0.0));
        _gObject->rotate(glm::vec3(1.0, 0.0, 0.0), M_PI / 2.0);
        _gObject->scale(glm::vec3(10.0, 1.0, 1.0));        
    }

    void update()
    {
        ;
    }

};

class Tower : public Component {

private:

public:

    Tower()
    {
        ;
    }

    void start()
    {
        _gObject->translate(glm::vec3(0.0, -1.0, -2.0));
        _gObject->scale(glm::vec3(0.3, 0.3, 0.3));
        _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), M_PI / 2.0);
    }

    void update()
    {
        ;
    }

};

class Parking : public Component {

private:

    const std::map<std::string, glm::vec3> parking_position = {
        {"a1", glm::vec3(4.0,  -0.5, -2.0)},
        {"a2", glm::vec3(6.0,  -0.5, -2.0)},
        {"a3", glm::vec3(8.0,  -0.5, -2.0)},
        {"a4", glm::vec3(-4.0, -0.5, -2.0)},
        {"a5", glm::vec3(-6.0, -0.5, -2.0)},
        {"a6", glm::vec3(-8.0, -0.5, -2.0)}
    };
    std::string _id;

public: 

    Parking(std::string id) 
    {
        this->_id = id;
    }

    void start()
    {
        GameObject *airplane = _gObject->search(this->_id);
        std::map<std::string, glm::vec3>::const_iterator it;
     
        it = parking_position.find(this->_id);

        airplane->translate(it->second);
        airplane->scale(glm::vec3(0.005, 0.005, 0.005));
    }
};


class Airplane : public Component {

public:

    Airplane()
    {
        ;
    }
 
    void start()
    {
        _gObject->translate(glm::vec3(-10.0, -0.5, 0.0));
        _gObject->scale(glm::vec3(0.005, 0.005, 0.005));
        _gObject->rotate(glm::vec3(0.0, 1.0, 0.0), M_PI / 2.0);
    }

    void update()
    {
        ;
    }
};

Light* getSunLightAirport()
{
    Directional *dir = new Directional("d");

    dir->setDirection(glm::vec3(0.0, -1.0, -1.0));
    dir->setIntense(1.0);
    return dir;
}

GameObject *generateSand(std::string id)
{
    GameObject *sand = new GameObject(id);
    Render *sandRender = new Render();
    Model *model = new Model("../models/sand/plane.obj");
    bool isFile = true;
    sandRender->setProgram(new Program(SandVertexShader, SandFragmentShader, !isFile));

    sandRender->setModel(model);

    sand->addDrawer(sandRender);
    sand->addComponent(new Sand());
    return sand;
}

GameObject *generateTower(std::string id)
{
    GameObject *road = new GameObject(id);
    Render *roadRender = new Render();
    Model *model = new Model("../models/tower/tower.obj");
    bool isFile = true;

    const std::string vpath = "../glsl/user/road_vs.glsl";
    const std::string fpath = "../glsl/user/road_fs.glsl";

    roadRender->setProgram(new Program(vpath, fpath, isFile));
    roadRender->setModel(model);
    road->addDrawer(roadRender);

    road->addComponent(new Camera());
    road->addComponent(new Tower());
    return road;
}

GameObject *generateRoad(std::string id)
{
    GameObject *road = new GameObject(id);
    Render *roadRender = new Render();
    Model *model = new Model("../models/road/plane.obj");
    bool isFile = true;


    const std::string vpath = "../glsl/user/road_vs.glsl";
    const std::string fpath = "../glsl/user/road_fs.glsl";

    roadRender->setProgram(new Program(vpath, fpath, isFile));
    roadRender->setModel(model);

    road->addDrawer(roadRender);
    road->addComponent(new Road());
    return road;
}

GameObject *generateAirplane(std::string id) 
{
    GameObject *airplane = new GameObject(id);
    Render *roadRender = new Render();
    Model *model = new Model("../models/airplane/airplane.obj");
    bool isFile = true;


    const std::string vpath = "../glsl/user/road_vs.glsl";
    const std::string fpath = "../glsl/user/road_fs.glsl";

    roadRender->setProgram(new Program(vpath, fpath, isFile));
    roadRender->setModel(model);

    airplane->addDrawer(roadRender);
    return airplane;
}

GameObject *getMountainSky(std::string id)
{
    GameObject *stars = new GameObject(id);

    SkyBox *skybox = new SkyBox(std::vector<std::string>({"../skybox/skybox/right.jpg", 
    "../skybox/skybox/left.jpg", "../skybox/skybox/top.jpg", 
    "../skybox/skybox/bottom.jpg", "../skybox/skybox/front.jpg", 
    "../skybox/skybox/back.jpg"}));

    stars->addDrawer(skybox);
    return stars;
}

void generateAirplanesParking(Scene *scene)
{
    for (uint32_t i = 0; i < AIRPLANES.size(); ++i) {
        GameObject *airplane = generateAirplane(AIRPLANES[i]);
        airplane->addComponent(new Parking(AIRPLANES[i]));
        scene->addChild(airplane);
    }
}

void generatePilotAirplane(Scene *scene)
{
    GameObject *airplane = generateAirplane("pilot");

    scene->addChild(airplane);
    airplane->addComponent(new Camera());
    airplane->addComponent(new Airplane());
}
Scene* AirportSimulation()
{
    Scene *scene = new Scene();

    GameObject *sand = generateSand("sand");
    GameObject *road = generateRoad("road");
    GameObject *tower = generateTower("tower");
    GameObject *mountainsSky = getMountainSky("sky"); 

    scene->addController(new UserController());
    scene->addLigth(getSunLightAirport());

    generateAirplanesParking(scene);
    generatePilotAirplane(scene);

    scene->addChild(mountainsSky);
    scene->addChild(tower);
    scene->addChild(road);
    scene->addChild(sand);

    return scene;
}
