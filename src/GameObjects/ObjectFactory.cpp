#include "GameObjects/ObjectFactory.hpp"

ObjectFactory::ObjectFactory() :
    _GameObjects()
{
//    std::cout << "Creating Factory Objects..." << '\n';
}

ObjectFactory::~ObjectFactory()
{
//    std::cout << "Delete All Game Objects!" << '\n'
    for (uint32_t i = 0; i < _GameObjects.size(); ++i) {
        delete _GameObjects[i];
    }
}

void ObjectFactory::addGameObject(GameObject *gameObject)
{
    _GameObjects.push_back(gameObject);
};

GameObject* ObjectFactory::getGameObject(unsigned id)
{
    return _GameObjects[id];
}

std::vector<GameObject*> ObjectFactory::getGameObjects()
{
    return _GameObjects;
}

void ObjectFactory::generateDemoObjects()
{
    this->simulation1();
//    this->solarSystem();
    // this->wallNormalMapping();
}
/*
void ObjectFactory::wallNormalMapping()
{
    std::string mesh_plane = "mesh_plane";
    Plane *plane = new Plane(mesh_plane);

    GameObject *wall_plane = new GameObject(0, " *** WALL *** ");
    Material *material = new Material(new Model(plane->getMesh()));
    material->setProgram(new Program("../glsl/wall_vs.glsl", "../glsl/wall_fs.glsl"));

    Texture *plane_diffuse = new Texture();
    plane_diffuse->type = "texture_normal";
    plane_diffuse->path = "../resources/";
    plane_diffuse->filename = "brickwall.jpg";
    material->setTexture(mesh_plane, plane_diffuse);

    Texture *plane_normal = new Texture();
    plane_normal->type = "texture_normal";
    plane_normal->path = "../resources/";
    plane_normal->filename = "brickwall_normal.jpg";
    material->setTexture(mesh_plane, plane_normal);

    wall_plane->addComponent(material);
    wall_plane->setMove(new Rotate(0.8, glm::vec3(1.0, 0.0, 0.0)));
//    plane->setPosition(new Position(glm::vec3(1.0, 0.0, 0.0), M_PI / 2.0f));
//    plane->setPosition(new Position(glm::vec3(0.0, 0.0, -1.0), M_PI / 12.0f));
    _GameObjects.push_back(wall_plane);
}
*/

/*
void ObjectFactory::solarSystem() {
//{
    // SUN
    GameObject *sun = new GameObject(0, "*** SUN ***");

    std::string sun_mesh = "sun_mesh";
    Sphere *sun_sphere = new Sphere(sun_mesh);
    Material *material_sun = new Material(new Model(sun_sphere->getMesh()));
    material_sun->setProgram(new Program("../glsl/sun_vs.glsl", "../glsl/sun_fs.glsl"));

    Texture *sun_diffuse = new Texture();
    sun_diffuse->type = "texture_diffuse";
    sun_diffuse->path = "../resources/";
    sun_diffuse->filename = "sun.png";
    material_sun->setTexture(sun_mesh, sun_diffuse);

    sun->setMove(new Translate(glm::vec3(0.0, 0.0, 0.0)));
    sun->addComponent(material_sun);
//}

//{
    // EARTH
    GameObject *earth = new GameObject(0, "*** EARTH ***");

    earth->setMove(new Rotate(0.3, glm::vec3(0.0, 1.0, 0.0)));
    earth->setMove(new Translate(glm::vec3(-2.0, 0.0, 0.0)));
    earth->setMove(new Rotate(0.8, glm::vec3(0.0, 1.0, -0.5)));
    earth->setMove(new Scale(glm::vec3(0.25, 0.25, 0.25)));

    std::string earth_mesh = "earth_sphere";
    Sphere *earth_sphere = new Sphere(earth_mesh);
    Material *material_earth = new Material(new Model(earth_sphere->getMesh()));
    material_earth->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    Texture *earth_diffuse = new Texture();
    earth_diffuse->type = "texture_diffuse";
    earth_diffuse->path = "../resources/";
    earth_diffuse->filename = "2k_earth_daymap.jpg";
    material_earth->setTexture(earth_mesh, earth_diffuse);

    Texture *earth_specular = new Texture();
    earth_specular->type = "texture_specular";
    earth_specular->path = "../resources/";
    earth_specular->filename = "2k_earth_specular_map.tif";
//    material_earth->setTexture(earth_mesh, earth_specular);

    Texture *earth_normal = new Texture();
    earth_normal->type = "texture_normal";
    earth_normal->path = "../resources/";
    earth_normal->filename = "2k_earth_normal_map.tif";
//    material_earth->setTexture(earth_mesh, earth_normal);

    earth->addComponent(material_earth);
    earth->addComponent(new Camera());

//}

//{
    // MARS
    GameObject *mars = new GameObject(0, "*** MARS ***");

    mars->setMove(new Rotate(0.3, glm::vec3(0.0, -1.0, 0.0)));
    mars->setMove(new Translate(glm::vec3(3.0, 0.0, 0.0)));
    mars->setMove(new Rotate(0.8, glm::vec3(0.0, -1.0, -0.1)));
    mars->setMove(new Scale(glm::vec3(0.25, 0.25, 0.25)));

    std::string mars_mesh = "mars_mesh";
    Sphere *mars_sphere = new Sphere(mars_mesh);

    Material *material_mars = new Material(new Model(mars_sphere->getMesh()));
    material_mars->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    Texture *mars_diffuse = new Texture();
    mars_diffuse->type = "texture_diffuse";
    mars_diffuse->path = "../resources/";
    mars_diffuse->filename = "mars.png";
    material_mars->setTexture(mars_mesh, mars_diffuse);

    mars->addComponent(material_mars);
    mars->addComponent(new Camera());
//}

//{
    // *** MOON ***
    GameObject *moon = new GameObject(0, "*** MOON ***");
    moon->setMove(new Rotate(2.3, glm::vec3(0.0, -1.0, 0.0)));
    moon->setMove(new Translate(glm::vec3(2.0, 0.0, 0.0)));
    moon->setMove(new Rotate(1.8, glm::vec3(0.0, -1.0, 0.0)));
    moon->setMove(new Scale(glm::vec3(0.15, 0.15, 0.15)));

    std::string moon_mesh = "moon_mesh";
    Sphere *sphere_moon = new Sphere(moon_mesh);
    Material *material_moon = new Material(new Model(sphere_moon->getMesh()));
    material_moon->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    Texture *moon_diffuse = new Texture();
    moon_diffuse->type = "texture_diffuse";
    moon_diffuse->path = "../resources/";
    moon_diffuse->filename = "moon.png";
    material_moon->setTexture(moon_mesh, moon_diffuse);

    moon->addComponent(material_moon);
    earth->addGameObject(moon);
//}

    // Skybox :)
    GameObject *skybox = new GameObject(0, "*** SKYBOX ***");
    skybox->addComponent(new SkyBox(std::vector<std::string> {
        "../skybox/ame_nebula/rigth.tga", "../skybox/ame_nebula/left.tga",
        "../skybox/ame_nebula/top.tga", "../skybox/ame_nebula/bottom.tga",
        "../skybox/ame_nebula/front.tga", "../skybox/ame_nebula/back.tga"
    }, new Program("../glsl/skybox_vs.glsl", "../glsl/skybox_fs.glsl")));
    skybox->setMove(new Scale(glm::vec3(10.0, 10.0, 10.0)));

    _GameObjects.push_back(sun);
    _GameObjects.push_back(skybox);
    sun->addGameObject(earth);
    sun->addGameObject(mars);
}
*/

void ObjectFactory::simulation1()
{

//    for (unsigned i = 0; i < _moves.size(); ++i) {
//        Material *grass = new Material(new Model(getPlantMesh("grass.png")), new Program("../glsl/grass_vs.glsl", "../glsl/grass_fs.glsl"));
//        grass->setTransparent();

//        GameObject *grass_go = new GameObject(i + 1, "**** GRASS **** ");
//        grass_go->addComponent(grass);
//        grass_go->setMove(_moves[i]);
//        _GameObjects.push_back(grass_go);
//    }
//    GameObject *_floor_go = new GameObject(0, "*** FLOOR ***");
//    _floor_go->addComponent(new Material(new Model(getPlaneMesh()), new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl")));
//    _floor_go->setMove(new Translate(glm::vec3(0.0, 0.0, 0.0)));
//    _GameObjects.push_back(_floor_go);

//    Material *nanosuit = new Material(new Model("../models/nanosuit/nanosuit.obj"), new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));
//    GameObject *nanosuit_go = new GameObject(30, "Complex model");
//    nanosuit_go->addComponent(nanosuit);
//    nanosuit_go->setMove(new Scale(glm::vec3(0.15, 0.15, 0.15)));
//    nanosuit_go->setMove(new Translate(glm::vec3(20.0, 0.0, 0.0)));
//    _GameObjects.push_back(nanosuit_go);

}

unsigned ObjectFactory::size() {
    return _GameObjects.size();
}
