#include "GameObjects/Scene.hpp"


Scene::Scene() :
    GameObject::GameObject()
{
    std::cout << "Create GameObject Scene" << '\n';
}

Scene::Scene(unsigned id, std::string name) :
    GameObject::GameObject(id, name)
{
    std::cout << "Create GameObject Scene" << '\n';
}

Scene::~Scene() {
    ;
}

Camera* Scene::getCamera() {
    std::vector<unsigned> keys = this->getKeysObjects();
    Camera *result = nullptr;

    for (unsigned i = 0; i < keys.size() && !result; ++i) {
        GameObject *gameObject = this->getGameObject(keys[i]);

        if (Camera *camera = dynamic_cast<Camera*>(gameObject)) {
            result = camera;
        }
    }
    return result;
}
