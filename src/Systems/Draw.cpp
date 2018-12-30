#include "Systems/Draw.hpp"

Draw::Draw() {
    std::cout << "Create system DRAW" << '\n';
}

Draw::~Draw() {
    std::cout << "Destroy system DRAW" << '\n';
}

void Draw::init(Scene *scene) {
    std::vector<unsigned> keys = scene->getKeysObjects();

    std::cout << "Init draw..." << '\n';
    for (unsigned i = 0; i < keys.size(); ++i) {
        GameObject *gameObject = scene->getGameObject(keys[i]);

        // Load Material...
        Component *component = gameObject->getComponent(TypeComp::MATERIAL);
        if (Material *material = dynamic_cast<Material*>(component)) {
            material->start();
        }
    }
    std::cout << "Draw Complete Initialize...." << '\n';
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
            Component *component = gameObject->getComponent(TypeComp::TRANSFORM);
            if (Transform *tf = dynamic_cast<Transform*>(component)) {
                material->setParameter("model", tf->_gModel);
            }
            material->setParameter("projection", cameras[scene->_camera]->_projection); // Vertex...
            material->setParameter("view", cameras[scene->_camera]->_tf->_gModel);      // Vertex...
            material->setParameter("viewPos", -cameras[scene->_camera]->_tf->position()); // Fragments...

            // Last step, uniforms first. After draw the object!!
            material->awakeStart();
        }
    }
}

void Draw::sendMessage(Message *msg)
{
    ;
}
