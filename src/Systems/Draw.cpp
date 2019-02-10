#include "Systems/Draw.hpp"

Draw::Draw() {
    std::cout << "Create system DRAW" << '\n';
}

Draw::~Draw() {
    std::cout << "Destroy system DRAW" << '\n';
}

void Draw::init(Scene *scene) {
    scene->init();
}

void Draw::update(float dt, Scene *scene) {
    scene->draw();
}

void Draw::sendMessage(Message *msg)
{
    ;
}
