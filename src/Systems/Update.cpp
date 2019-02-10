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
    scene->update();
}

void Update::models(float dt, GameObject *scene) {
}

void Update::sendMessage(Message *msg) {
    std::cout << "Send system message update... " << '\n';
}
