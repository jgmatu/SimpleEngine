#include "Systems/Update.hpp"

Update::Update() {
    std::cout << "Create system UPDATE" << '\n';
}

Update::~Update() {
    std::cout << "Destroy system update... " << '\n';
}

void Update::init(Scene *scene) {
    ;
}

void Update::update(float dt, Scene *scene) {
    this->models(dt, scene);
}

void Update::models(float dt, GameObject *scene) {
    for (unsigned i = 0; i < scene->_gameObjects.size(); ++i) {
        GameObject *gameObj = scene->_gameObjects[i];

        Component *component = gameObj->getComponent(TypeComp::TRANSFORM);
        if (Transform *tfObj = dynamic_cast<Transform*>(component)) {
            component = scene->getComponent(TypeComp::TRANSFORM);

            tfObj->update();
            if (Transform *tfScene = dynamic_cast<Transform*>(component)) {
                tfObj->_gModel = tfScene->_gModel * tfObj->_model;
            }
        }
        this->models(dt, gameObj);
    }
}

void Update::sendMessage(Message *msg) {
    std::cout << "Send system message update... " << '\n';
}
