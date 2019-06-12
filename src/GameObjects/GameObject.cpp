#include "GameObjects/GameObject.hpp"

GameObject::GameObject() :
    _components(),
    _gameObjects()
{
    _tf = new Transform();
    _components.push_back(_tf);
}

GameObject::~GameObject() {
    size_t size = _gameObjects.size();

    for (uint32_t i = 0; i < size; ++i) {
        delete _gameObjects[i];
    }

    size = _components.size();
    for (uint32_t i = 0; i < size; ++i) {
        delete _components[i];
    }
}

void GameObject::getCameras(std::vector<Camera*>& cameras)
{
    size_t components_size = _components.size();

    for (uint32_t i = 0; i < components_size; ++i) {
        if (Camera *camera = dynamic_cast<Camera*>(_components[i])) {
            cameras.push_back(camera);
        }
    }

    size_t gameObjects_size = _gameObjects.size();

    for (uint32_t i = 0; i < gameObjects_size; ++i) {
        _gameObjects[i]->getCameras(cameras);
    }
};

Component* GameObject::getComponent(TypeComp type) const {
    Component* search = nullptr;

    for (uint32_t i = 0; !search && i < _components.size(); ++i) {
        if (_components[i]->_type == type) {
            search = _components[i];
        }
    }
    return search;
}

void GameObject::addComponent(Component *component) {
    if (Camera *camera = dynamic_cast<Camera*>(component)) {
        camera->_tfObj = this->_tf;
    }
    _components.push_back(component);
}

void GameObject::addChild(GameObject *gameObject) {
    _tf->addChild(gameObject->_tf);
    _gameObjects.push_back(gameObject);
}

void GameObject::init() {
    Component *component = this->getComponent(TypeComp::MATERIAL);

    if (Material *material = dynamic_cast<Material*>(component)) {
        material->start();
    }
    component = this->getComponent(TypeComp::SKYBOX);
    if (SkyBox *skybox = dynamic_cast<SkyBox*>(component)) {
        skybox->start();
    }
    for (unsigned i = 0; i < _gameObjects.size(); ++i) {
        _gameObjects[i]->init();
    }
}

void GameObject::addTransparentQueue(std::map<float, std::vector<GameObject*>>& sorted, float distance) {
    std::map<float, std::vector<GameObject*>>::iterator it;
    it = sorted.find(distance);

    if (it == sorted.end()) {
        std::vector<GameObject*> aux;
        aux.push_back(this);
        sorted[distance] = aux;
    } else {
        it->second.push_back(this);
    }
}

// Obtener la componente camara activa... Camara activa de todos los gameObject
// de la escena... (Escena...) dibujar todos los gameObject respecto a la camara activa
// de la escena...
void GameObject::draw(Camera *camera) {
    Component *component = this->getComponent(TypeComp::MATERIAL);

    if (Material *material = dynamic_cast<Material*>(component)) {
        Component *component = this->getComponent(TypeComp::TRANSFORM);
        if (Transform *tf = dynamic_cast<Transform*>(component)) {
            material->setParameter("model", tf->_gModel);
        }
        material->setView(camera);
        material->awakeStart();
    }
}

void GameObject::draw(Camera *active_camera, std::map<float, std::vector<GameObject*>>& sorted) {
    Component *component = getComponent(TypeComp::MATERIAL);

    if (Material *material = dynamic_cast<Material*>(component)) {
        if (material->isTransparent()) {
            Component *component = getComponent(TypeComp::TRANSFORM);
            if (Transform *tf = dynamic_cast<Transform*>(component)) {
                float distance = glm::length(active_camera->_view->position() - tf->position());
                this->addTransparentQueue(sorted, distance);
            }
        } else {
            this->draw(active_camera);
        }
    }
    component = getComponent(TypeComp::SKYBOX);
    // GameObject with a SkyBox...
    if (SkyBox *skybox = dynamic_cast<SkyBox*>(component)) {
        skybox->setView(active_camera);
        skybox->awakeStart();
    }

    for (unsigned i = 0; i < _gameObjects.size(); ++i) {
        _gameObjects[i]->draw(active_camera, sorted);
    }
}

void GameObject::update()
{
    size_t size = _components.size();

    for (uint32_t i = 0; i < size; ++i) {
        _components[i]->update();
    }

    size = _gameObjects.size();
    for (uint32_t i = 0; i < size; ++i) {
        _gameObjects[i]->update();
    }
}

void GameObject::addLigths(std::vector<Light*> ligths) {
    Component *component = this->getComponent(TypeComp::MATERIAL);

    if (Material *material = dynamic_cast<Material*>(component)) {
        material->addLigths(ligths);
    }
    for (unsigned i = 0; i < _gameObjects.size(); ++i) {
        _gameObjects[i]->addLigths(ligths);
    }
}

std::ostream& operator<<(std::ostream& os, const GameObject& gameObject) {
    os << gameObject._name << std::endl;
    Component *component = gameObject.getComponent(TypeComp::TRANSFORM);
    if (Transform *tf = dynamic_cast<Transform*>(component)) {
        os << (*tf);
    }

    component = gameObject.getComponent(TypeComp::MATERIAL);
    if (Material *material = dynamic_cast<Material*>(component)) {
        os << (*material);
    }
    return os;
}
