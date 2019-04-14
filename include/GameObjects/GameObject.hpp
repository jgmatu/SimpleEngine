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

#include "Operations/Movement.hpp"

class Camera;

class GameObject {

    friend class Update;
    friend class Scene;

public:

    GameObject();
    GameObject(int id, std::string _name);
    virtual ~GameObject();

    Component* getComponent(TypeComp type) const;
    void addComponent(Component *component);
    bool hasComponent(TypeComp type);

    GameObject* getGameObject(int id);
    bool hasGameObject(int id);
    void addGameObject(GameObject *gameObject);

    void init();
    void draw(Camera *camera);
    void draw(Camera *active_camera, std::map<float, std::vector<GameObject*>>& sorted);
    void update();

    void setMoves(std::vector<Movement*> moves);
    void setMove(Movement *move);

    void addLigths(std::vector<Light*> ligths);
    void addGameObjects(std::vector<GameObject*> objects) {
        this->_gameObjects = objects;
    }

    friend std::ostream& operator<<(std::ostream&, const GameObject& gameObject);

protected:

    int _id;
    std::string _name;

    std::vector<Component*> _components;
    std::vector<GameObject*> _gameObjects;

private:

    void addTransparentQueue(std::map<float, std::vector<GameObject*>>& sorted, float distance);
    void updateCamera();

};

#endif
