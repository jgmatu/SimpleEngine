#include "Systems/Draw.hpp"

Draw::Draw() {
    std::cout << "Create system draw... " << '\n';
}

Draw::~Draw() {
    std::cout << "Destroy system draw... " << '\n';
}

void Draw::init(std::vector<GameObject*> _GameObjects) {
    ;
}

void Draw::update(float dt, std::vector<GameObject*> _GameObjects) {
    ;
}

void Draw::sendMessage (Message *msg) {
    ;
}
