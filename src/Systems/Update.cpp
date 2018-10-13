#include "Systems/Update.hpp"

Update::Update() {
    std::cout << "Create system UPDATE" << '\n';
}

Update::~Update() {
    std::cout << "Destroy system update... " << '\n';
}

void Update::init(Scene *scene) {
    std::cout << "|Init system Update|" << '\n';
    std::vector<unsigned> keys = scene->getKeysObjects();

    for (unsigned i = 0; i < keys.size(); ++i) {
        GameObject *gameObject = scene->getGameObject(keys[i]);
        Component *component = gameObject->getComponent(TypeComp::TRANSFORM);

        if (Transform *tf =  dynamic_cast<Transform*>(component)) {
            tf->start();
        }
    }
}

void Update::update(float dt, Scene *scene) {
    std::cout << "|update system Update|" << '\n';
    std::vector<unsigned> keys = scene->getKeysObjects();

    for (unsigned i = 0; i < keys.size(); ++i) {
        GameObject *gameObject = scene->getGameObject(keys[i]);
        Component *component = gameObject->getComponent(TypeComp::TRANSFORM);

        if (Transform *tf =  dynamic_cast<Transform*>(component)) {
            tf->update();
        }
    }
}

void Update::sendMessage (Message *msg) {
    std::cout << "Send system message update... " << '\n';
}
