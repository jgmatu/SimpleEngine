#include "Systems/Draw.hpp"

Draw::Draw() {
    std::cout << "Create system DRAW" << '\n';
}

Draw::~Draw() {
    std::cout << "Destroy system DRAW" << '\n';
}

void Draw::init(Scene *scene) {
    std::cout << "|Init system Draw|" << '\n';
    std::vector<unsigned> keys = scene->getKeysObjects();

    for (unsigned i = 0; i < keys.size(); ++i) {
        GameObject *gameObject = scene->getGameObject(keys[i]);
        Component *component = gameObject->getComponent(TypeComp::MATERIAL);

        if(Material *material = dynamic_cast<Material*>(component)) {
            material->start();
        }
    }
}

void Draw::update(float dt, Scene *scene) {
    std::cout << "|Update system Draw|" << '\n';
    std::vector<unsigned> keys = scene->getKeysObjects();

    for (unsigned i = 0; i < keys.size(); ++i) {
        GameObject *gameObject = scene->getGameObject(keys[i]);
        Component *component = gameObject->getComponent(TypeComp::MATERIAL);

        if (Material *material = dynamic_cast<Material*>(component)) {
            material->awakeStart();
        }
    }
}

void Draw::sendMessage (Message *msg) {
    ;
}
