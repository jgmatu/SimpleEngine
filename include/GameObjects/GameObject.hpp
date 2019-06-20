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
#include "Components/Material.hpp"
#include "Components/SkyBox.hpp"

#include "Constants/TypeComp.hpp"

class Camera;
class Keyboard;
class Clock;

class GameObject {

    friend class Update;
    friend class Scene;

public:

    GameObject();
    virtual ~GameObject();

    void addComponent(Component *component);
    Component* getComponent(TypeComp type) const;
    void addChild(GameObject *gameObject);

    void init();

    void draw(Camera *camera);
    void draw(Camera *active_camera, std::map<float, std::vector<GameObject*>>& sorted);

    void update();

    void scale(glm::vec3 vec3);
    void translate(glm::vec3 vec3);
    void rotate(glm::vec3 vec3, glm::quat quad);
    void rotate(glm::vec3 vec3, float angle);

    void addLigths(std::vector<Light*> ligths);
    void addGameObjects(std::vector<GameObject*> objects) {
        this->_gameObjects = objects;
    }

    void getCameras(std::vector<Camera*>& cameras);
    void setSystems(Keyboard *keyboard, Clock *_clock);

    friend std::ostream& operator<<(std::ostream&, const GameObject& gameObject);

protected:

    int _id;
    std::string _name;

    std::vector<Component*> _components;
    std::vector<GameObject*> _gameObjects;

    Transform *_tf;

private:

    void addTransparentQueue(std::map<float, std::vector<GameObject*>>& sorted, float distance);
    void updateChildsTransform();

};

#endif
