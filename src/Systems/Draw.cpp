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

        // Load texture...
        component = gameObject->getComponent(TypeComp::TEXTURE);
        if (Texture *texture = dynamic_cast<Texture*>(component)) {
            texture->start();
        }

        // Ambient...
        component = gameObject->getComponent(TypeComp::LIGTH_AMBIENT);
        if (Ambient *ambient = dynamic_cast<Ambient*>(component)) {
            ambient->start();
        }

        // Diffuse...
        component = gameObject->getComponent(TypeComp::LIGTH_DIFFUSE);
        if (Diffuse *diffuse = dynamic_cast<Diffuse*>(component)) {
            diffuse->start();
        }

        // Specular...
        component = gameObject->getComponent(TypeComp::LIGTH_SPECULAR);
        if (Specular *specular = dynamic_cast<Specular*>(component)) {
            specular->start();
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
            material->setParameter("projection", cameras[scene->_camera]->_projection);
            material->setParameter("view", cameras[scene->_camera]->_tf->_gModel);
            material->setParameter("diffuseTexture", 0);  // El índice es el mismo que en glActiveTexture(), "Número de textura...";

            Component *component = gameObject->getComponent(TypeComp::TRANSFORM);
            if (Transform *tf = dynamic_cast<Transform*>(component)) {
                material->setParameter("model", tf->_gModel);
            }

            component = gameObject->getComponent(TypeComp::TEXTURE);
            if (Texture *texture = dynamic_cast<Texture*>(component)) {
                texture->awakeStart();
            }
            // Last step, uniforms first after draw the object!!
            material->update();
        }
    }
}

void Draw::sendMessage(Message *msg) {
    ;
}
