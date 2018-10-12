#include "Systems/Update.hpp"

Update::Update() {
    std::cout << "Create system update... " << '\n';
}

Update::~Update() {
    std::cout << "Destroy system update... " << '\n';
}

void Update::init(std::vector<GameObject*> _GameObjects) {
    std::cout << "Init system update... " << '\n';
}

void Update::update(float dt, std::vector<GameObject*> _GameObjects) {
    std::cout << "Update system update... " << '\n';
}

void Update::sendMessage (Message *msg) {
    std::cout << "Send system message update... " << '\n';
}
