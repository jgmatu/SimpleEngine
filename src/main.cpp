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

#include "Systems/Draw.hpp"
#include "Systems/Update.hpp"
#include "Systems/Keyboard.hpp"

#include "Engine.hpp"

class Example : public Component {

private:

    GameObject *_gameObject;

public:

    Example(GameObject *gameObject)
    {
        this->_gameObject = gameObject;
    }

    ~Example()
    {

    }

    void start()
    {
        _gameObject->translate(glm::vec3(0.0, 0.0, -5.0));
    }

    void update(Keyboard *keyboard, Clock *_clock)
    {
        if (keyboard->isKeyPressed("a")) {
            _gameObject->rotate(glm::vec3(1.0, 0.0, 0.0), 0.01);
            _gameObject->rotate(glm::vec3(0.0, 1.0, 0.0), 0.01);
        }
    }

    void awakeStart()
    {
        ;
    }

};

Scene* sceneSimulation()
{
    GameObject *cube = new GameObject();

    std::string id_mesh = "cube_mesh";
    Cube *geometry_cube = new Cube(id_mesh);
    Material *material = new Material(new Model(geometry_cube->getMesh()));
    material->setProgram(new Program("../glsl/vertex.glsl", "../glsl/fragment.glsl"));

    __Texture__ *diffuse = new __Texture__();
    diffuse->type = "texture_diffuse";
    diffuse->path = "../resources";
    diffuse->filename = "container2.png";
    material->setTexture(id_mesh, diffuse);

    __Texture__ *specular = new __Texture__();
    specular->type = "texture_specular";
    specular->path = "../resources";
    specular->filename = "container2_specular.png";
    material->setTexture(id_mesh, specular);

    cube->addComponent(material);
    cube->addComponent(new Camera());
    cube->addComponent(new Example(cube));

    Scene *scene = new Scene();
    scene->addChild(cube);

    return scene;
}

int main(int argc, char* argv[]) {
    Engine *engine = nullptr;

    try {
        engine = new Engine(sceneSimulation());
        engine->add(new Update());
        engine->add(new Draw());
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
