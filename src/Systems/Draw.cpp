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
        std::shared_ptr<Component> component = gameObject->getComponent(TypeComp::MATERIAL);

        if(std::shared_ptr<Material> material = std::dynamic_pointer_cast<Material>(component)) {
            material->start();
            material->addTexture("../resources/textura.png");
            material->createUniform("projection");
            material->createUniform("view");
            material->createUniform("model");
            material->createUniform("diffuseTexture");
        }
    }
}

void Draw::update(float dt, Scene *scene) {
    std::cout << "*** Update system Draw ***" << '\n';
    std::vector<unsigned> keys = scene->getKeysObjects();

    for (unsigned i = 0; i < keys.size(); ++i) {
        GameObject *gameObject = scene->getGameObject(keys[i]);
        std::shared_ptr<Component> component = gameObject->getComponent(TypeComp::MATERIAL);

        if (std::shared_ptr<Material> material = std::dynamic_pointer_cast<Material>(component)) {
            Camera* camera = scene->getCamera();
            material->setUniform("projection", camera->_projection);
            material->setUniform("view", camera->_view);
            material->setUniform("diffuseTexture", 0);  // El índice es el mismo que en glActiveTexture()
            material->awakeStart();

            std::shared_ptr<Component> component = gameObject->getComponent(TypeComp::TRANSFORM);
            if (std::shared_ptr<Transform> tf = std::dynamic_pointer_cast<Transform>(component)) {
                material->setUniform("model", tf->model());
            }
        }
    }
}

void Draw::sendMessage(Message *msg) {
    ;
}
