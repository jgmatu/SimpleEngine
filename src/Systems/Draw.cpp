#include "Systems/Draw.hpp"

Draw::Draw() {
    std::cout << "Create system DRAW" << '\n';
}

Draw::~Draw() {
    std::cout << "Destroy system DRAW" << '\n';
}

void Draw::init(Scene *scene) {
    std::vector<unsigned> keys = scene->getKeysObjects();

    for (unsigned i = 0; i < keys.size(); ++i) {
        GameObject *gameObject = scene->getGameObject(keys[i]);
        Component *component = gameObject->getComponent(TypeComp::MATERIAL);

        if(Material *material = dynamic_cast<Material*>(component)) {
            material->start();
            material->createUniform("projection");
            material->createUniform("view");
            material->createUniform("model");
            material->createUniform("diffuseTexture");
        }
    }
}

void Draw::update(float dt, Scene *scene) {

    // ** Update cameras **/
    std::vector<Camera*> cameras = scene->_cameras;
    for (unsigned i = 0; i < scene->MAX_CAMERAS; ++i) {
        cameras[i]->update();
    }

    // ** Update Game Objects **/
    std::vector<unsigned> keys = scene->getKeysObjects();

    for (unsigned i = 0; i < keys.size(); ++i) {
        GameObject *gameObject = scene->getGameObject(keys[i]);
        Component *component = gameObject->getComponent(TypeComp::MATERIAL);

        if (Material *material = dynamic_cast<Material*>(component)) {
            material->setUniform("projection", cameras[scene->_camera]->_projection);
            material->setUniform("view", cameras[scene->_camera]->_tf->_gModel);
            material->setUniform("diffuseTexture", 0);  // El índice es el mismo que en glActiveTexture()

            Component *component = gameObject->getComponent(TypeComp::TRANSFORM);
            if (Transform *tf = dynamic_cast<Transform*>(component)) {
                material->setUniform("model", tf->_gModel);
            }
            // Last step, uniforms first after draw the object!!
            material->update();
        }
    }
}

void Draw::sendMessage(Message *msg) {
    ;
}
