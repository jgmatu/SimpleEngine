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

std::vector<Camera*> Draw::updateCameras(Scene *scene)
{
    std::vector<Camera*> cameras = scene->_cameras;

    for (unsigned i = 0; i < scene->MAX_CAMERAS; ++i) {
        cameras[i]->update();
    }
    return cameras;
}

void Draw::draw(Camera *camera, GameObject *gameObject)
{
    Component *component = gameObject->getComponent(TypeComp::MATERIAL);
    if (Material *material = dynamic_cast<Material*>(component)) {
        Component *component = gameObject->getComponent(TypeComp::TRANSFORM);
        if (Transform *tf = dynamic_cast<Transform*>(component)) {
            material->setParameter("model", tf->_gModel);
        }
        material->setParameter("projection", camera->_projection); // Vertex...
        material->setParameter("view", camera->_tf->_gModel);      // Vertex...
        material->setParameter("viewPos", -camera->_tf->position()); // Fragments...
        // Last step, uniforms first. After draw the object!!
        material->awakeStart();
    }
}

void Draw::update(float dt, Scene *scene) {
    std::vector<Camera*> cameras = this->updateCameras(scene);
    std::vector<unsigned> keys = scene->getKeysObjects();
    std::map<float, GameObject*> sorted;

    for (unsigned i = 0; i < keys.size(); ++i) {
        GameObject *gameObject = scene->getGameObject(keys[i]);

        Component *component = gameObject->getComponent(TypeComp::MATERIAL);
        if (Material *material = dynamic_cast<Material*>(component)) {
            if (material->isTransparent()) {
                Component *component = gameObject->getComponent(TypeComp::TRANSFORM);
                if (Transform *tf = dynamic_cast<Transform*>(component)) {
                    float distance = glm::length(-cameras[scene->_camera]->_tf->position() - tf->position());
                    sorted[distance] = gameObject;
                }
            } else {
                // Opaque objects draw first and in any order...
                this->draw(cameras[scene->_camera], gameObject);
            }
        }
    }
    for(std::map<float, GameObject*>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it) {
        // Draw sorted transparent objects on the scene...
        this->draw(cameras[scene->_camera], it->second);
    }
}

void Draw::sendMessage(Message *msg)
{
    ;
}
