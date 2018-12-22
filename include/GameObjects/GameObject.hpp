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
#include "Constants/TypeComp.hpp"

class GameObject {

    friend class Update;
    friend class Scene;

public:

    GameObject();
    GameObject(unsigned id, std::string _name);
    virtual ~GameObject();


    Component* getComponent(TypeComp type) const;
    void addComponent(Component *component);
    bool hasComponent(TypeComp type);

    GameObject* getGameObject(unsigned id);
    bool hasGameObject(unsigned id);
    void addGameObject(GameObject *gameObject);

    std::vector<unsigned> getKeysObjects();

    void scale(glm::vec3 vec3);
    void translate(glm::vec3 vec3);
    void rotate(glm::vec3 vec3, glm::quat quat);
    void rotate(glm::vec3 vec3, float angle);

    friend std::ostream& operator<<(std::ostream&, const GameObject& gameObject);

protected:

    unsigned _id;
    std::string _name;

    std::vector<Component*> _components;
    std::vector<GameObject*> _gameObjects;
};

#endif
