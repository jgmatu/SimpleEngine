#include "GameObjects/GameObject.hpp"

GameObject::GameObject() :
    _id(-1),
    _name("?"),
    _components(),
    _gameObjects()
{
    _components.push_back(new Transform());
}

GameObject::GameObject(int id, std::string name) :
    GameObject()
{
    this->_id = id;
    this->_name = name;
}

GameObject::~GameObject() {
    for (unsigned i = 0; i < _gameObjects.size(); ++i) {
        delete _gameObjects[i];
    }
}

void GameObject::setMoves(std::vector<Movement*> moves)
{
    Component *component = this->getComponent(TypeComp::TRANSFORM);

    if (Transform *tf = dynamic_cast<Transform*>(component)) {
        tf->_moves = moves;
    }
}

void GameObject::setMove(Movement *move) {
    Component *component = this->getComponent(TypeComp::TRANSFORM);

    if (Transform *tf = dynamic_cast<Transform*>(component)) {
        tf->_moves.push_back(move);
    }
}

Component* GameObject::getComponent(TypeComp type) const {
    Component* search = nullptr;

    for (unsigned i = 0; !search && i < _components.size(); ++i) {
        if (_components[i]->_type == type) {
            search = _components[i];
        }
    }
    return search;
}

void GameObject::addComponent(Component *component) {
    _components.push_back(component);
}

bool GameObject::hasComponent(TypeComp type) {
    for (unsigned i = 0; i < _components.size(); ++i) {
        if (_components[i]->_type == type) {
            return true;
        }
    }
    return false;
}

GameObject* GameObject::getGameObject(int id) {
    GameObject *search = nullptr;

    for (unsigned i = 0; !search && i < _gameObjects.size(); ++i) {
        if (_gameObjects[i]->_id == id) {
            search = _gameObjects[i];
        } else {
            search = _gameObjects[i]->getGameObject(id);
        }
    }
    return search;
}

void GameObject::addGameObject(GameObject *gameObject) {
    _gameObjects.push_back(gameObject);
}

bool GameObject::hasGameObject(int id) {
    for (unsigned i = 0; i < _gameObjects.size(); ++i) {
        if (id == _gameObjects[i]->_id) {
            return true;
        }
        _gameObjects[i]->hasGameObject(id);
    }
    return false;
}

void GameObject::init() {
    Component *component = this->getComponent(TypeComp::MATERIAL);
    if (Material *material = dynamic_cast<Material*>(component)) {
        // Load Material...
        material->start();
    }
    for (unsigned i = 0; i < _gameObjects.size(); ++i) {
        _gameObjects[i]->init();
    }
}

void GameObject::draw(Camera *active_camera, std::map<float, std::vector<GameObject*>>& sorted) {
    Component *component = getComponent(TypeComp::MATERIAL);

    if (Material *material = dynamic_cast<Material*>(component)) {
        if (material->isTransparent()) {
            Component *component = getComponent(TypeComp::TRANSFORM);
            if (Transform *tf = dynamic_cast<Transform*>(component)) {
                float distance = glm::length(-active_camera->_view->position() - tf->position());
                this->addTransparentQueue(sorted, distance);
            }
        } else {
            this->draw(active_camera);
        }
    }
    for (unsigned i = 0; i < _gameObjects.size(); ++i) {
        _gameObjects[i]->draw(active_camera, sorted);
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

void GameObject::update() {
    this->updateCamera();

    Component *component = this->getComponent(TypeComp::TRANSFORM);

    if (Transform *tfRoot = dynamic_cast<Transform*>(component)) {
        for (unsigned i = 0; i < _gameObjects.size(); ++i) {
            component = _gameObjects[i]->getComponent(TypeComp::TRANSFORM);
            if (Transform *tfChild = dynamic_cast<Transform*>(component)) {
                tfChild->update();
                tfChild->_gModel = tfRoot->_gModel * tfChild->_model;
            }
            _gameObjects[i]->update();
        }
    }
}

void GameObject::updateCamera()
{
    Component *component = this->getComponent(TypeComp::CAMERA);

    if (Camera *camera = dynamic_cast<Camera*>(component)) {
        component = this->getComponent(TypeComp::TRANSFORM);
        if (Transform *tf = dynamic_cast<Transform*>(component)) {
            camera->_view->_gModel = tf->_gModel * camera->_view->_model;
            camera->_view->_gModel = glm::inverse(camera->_view->_gModel);
        }
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
