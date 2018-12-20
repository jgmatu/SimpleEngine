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
        Component *component = gameObject->getComponent(TypeComp::MATERIAL);

        if (Material *material = dynamic_cast<Material*>(component)) {
            material->start();
        }

        component = gameObject->getComponent(TypeComp::LIGTH);
        if (Light *light = dynamic_cast<Light*>(component)) {
            // Ambient...
            if (Ambient *ambient = dynamic_cast<Ambient*>(light)) {
                ambient->start();
            }
            // Difuse...
            if (Diffuse *diffuse = dynamic_cast<Diffuse*>(light)) {
                diffuse->start();
            }
            // Specular...
            if (Specular *specular = dynamic_cast<Specular*>(light)) {
                specular->start();
            }
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
            material->setParameter("diffuseTexture", 0);  // El índice es el mismo que en glActiveTexture()

            Component *component = gameObject->getComponent(TypeComp::TRANSFORM);
            if (Transform *tf = dynamic_cast<Transform*>(component)) {
                material->setParameter("model", tf->_gModel);
            }

            component = gameObject->getComponent(TypeComp::LIGTH);
            if (Light *light = dynamic_cast<Light*>(component)) {
                // Ambient...
                if (Ambient *ambient = dynamic_cast<Ambient*>(light)) {
                    ambient->update();
                }
                // Difuse...
                if (Diffuse *diffuse = dynamic_cast<Diffuse*>(light)) {
                    diffuse->update();
                }
                // Specular...
                if (Specular *specular = dynamic_cast<Specular*>(light)) {
                    specular->update();
                }
            }
            // Last step, uniforms first after draw the object!!
            material->update();
        }
    }
}

void Draw::sendMessage(Message *msg) {
    ;
}
