#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#define GLM_ENABLE_EXPERIMENTAL

#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include "Components/Component.hpp"
#include "Components/Transform.hpp"

#include "Drawers/Drawer.hpp"
#include "Drawers/Skybox.hpp"
#include "Drawers/Render.hpp"

class Camera;

class GameObject {

public:

    GameObject(std::string id);
    virtual ~GameObject();

    void addChild(GameObject *gameObject);

    void addComponent(Component *component);
    void addDrawer(Drawer *drawer);

    void scale(glm::vec3 vec3);
    void translate(glm::vec3 vec3);
    void rotate(glm::vec3 vec3, glm::quat quad);
    void rotate(glm::vec3 vec3, float angle);
    void reset();

    float distance(std::string id);

    void addLigths(std::vector<Light*> ligths);
    std::vector<Light*> getLigths();
    Light* getLigth(std::string id);

    void setColor(glm::vec3 rgb);

    friend std::ostream& operator<<(std::ostream&, const GameObject& gameObject);

protected:

    std::string _id;
    GameObject *_root;

    std::vector<Component*> _components;
    std::vector<Drawer*> _drawers;

    std::vector<GameObject*> _gameObjects;
    std::vector<Light*> _ligths;

    Transform *_tf;
    Camera *_camera;

private:

    GameObject();

    void init();
    void update();

    void active();
    void draw();

    void getCameras(std::vector<Camera*>& cameras);
    void setCamera(Camera *camera) {
        this->_camera = camera;
    };
    void getQueueDrawGameObjects(
        std::map<float, std::vector<GameObject*>>& transparents,
        std::vector<GameObject*>& opaques
    );
    void addTransparentQueue(std::map<float, std::vector<GameObject*>>& transparents);

    GameObject* search(std::string id);
    GameObject* _search(std::string id);

    friend class Scene;
};

#endif
