#include "GameObjects/GameObject.hpp"

GameObject::GameObject() :
    _components(),
    _gameObjects()
{
    _tf = new Transform();
    _components.push_back(_tf);
}

GameObject::GameObject(std::string id) :
    GameObject::GameObject()
{
    this->_id = id;
}

GameObject::~GameObject() {
    size_t size = _components.size();

    for (uint32_t i = 0; i < size; ++i) {
        delete _components[i];
    }

    size = _drawers.size();
    for (uint32_t i = 0; i < size; ++i) {
        delete _drawers[i];
    }

    size = _gameObjects.size();
    for (uint32_t i = 0; i < size; ++i) {
        delete _gameObjects[i];
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

GameObject *GameObject::search(std::string id)
{   
    return this->_root->_search(id);
}

GameObject *GameObject::_search(std::string id)
{
    std::vector<GameObject*>::const_iterator it;
    GameObject *found = nullptr;

    for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it) {
        if ((*it)->_id.compare(id) == 0) {
            return (*it);
        }
    }
    for (it = _gameObjects.begin(); it != _gameObjects.end() && !found; ++it) {
        found = (*it)->_search(id);
    }
    return found;
}

void GameObject::addComponent(Component *component) {
    if (Camera *camera = dynamic_cast<Camera*>(component)) {
        camera->_tfObj = this->_tf;
    }
    component->_gObject = this;
    _components.push_back(component);
}

void GameObject::deleteComponent(Component *component)
{
    size_t size = _components.size();
    for (uint32_t i = 0; i < size; ++i) {
        if (_components[i] == component) {
            _components.erase(_components.begin() + i);
        }
    }
}

void GameObject::addDrawer(Drawer *drawer)
{
    _drawers.push_back(drawer);
}

void GameObject::addChild(GameObject *gameObject) {
    if (this->_root && search(gameObject->_id)) {
        std::cerr << "This gameObject already exist on the scene..." << '\n';
        throw;
    }
    gameObject->_root = this->_root;
    this->_tf->addChild(gameObject->_tf);
    this->_gameObjects.push_back(gameObject);

}

void GameObject::active()
{
    size_t drawers_size = _drawers.size();
    size_t gameObjects_size = _gameObjects.size();

    std::cout << "Game object active..." << std::endl;
    for (uint32_t i = 0; i < drawers_size; ++i) {
        _drawers[i]->active();
    }
    for (uint32_t i = 0; i < gameObjects_size; ++i) {
        _gameObjects[i]->active();
    }
}

void GameObject::init()
{
    size_t components_size  = _components.size();
    size_t gameObjects_size = _gameObjects.size();
    Transform *tf = nullptr;

    for (uint32_t i = 0; i < components_size; ++i) {
        if (!tf) {
            if ((tf = dynamic_cast<Transform*>(_components[i])) != nullptr) {
                continue;
            }
        }
        _components[i]->start();
    }
    if (!tf) {
        std::cerr << "TF NULL" << std::endl;
        throw;
    }
    tf->start();

    for (uint32_t i = 0; i < gameObjects_size; ++i) {
        _gameObjects[i]->init();
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

void GameObject::draw()
{
    for (uint32_t i = 0; i < _drawers.size(); ++i) {
        if (Render *render = dynamic_cast<Render*>(_drawers[i])) {
            render->setMatrixModel(_tf->_gModel);   
        }
        _drawers[i]->setView(_camera);
        _drawers[i]->draw();
    }
}

void GameObject::getQueueDrawGameObjects(
    std::map<float, std::vector<GameObject*>>& transparents,
    std::vector<GameObject*>& opaques)
{
    for (uint32_t i = 0; i < _drawers.size(); ++i) {
        if (Render *render = dynamic_cast<Render*>(_drawers[i])) {
            if (render->isTransparentModel()) {
                addTransparentQueue(transparents);
            } else {
                opaques.push_back(this);
            }
        } else {
            opaques.push_back(this);
        }
    }

    for (uint32_t i = 0; i < _gameObjects.size(); ++i) {
        _gameObjects[i]->setCamera(_camera);
        _gameObjects[i]->getQueueDrawGameObjects(transparents, opaques);
    }
}

void GameObject::addTransparentQueue(std::map<float, std::vector<GameObject*>>& transparents)
{
    std::map<float, std::vector<GameObject*>>::iterator it;
    std::vector<GameObject*> aux;
    float distance;

    distance = glm::distance(_camera->_view->position(), this->_tf->position());
    it = transparents.find(distance);

    if (it == transparents.end()) {
        aux.push_back(this);
        transparents[distance] = aux;
    } else {
        it->second.push_back(this);
    }
}

void GameObject::addLigths(std::vector<Light*> ligths)
{
    this->_ligths = ligths;

    for (uint32_t i = 0; i < _drawers.size(); ++i) {
        if (Render *render = dynamic_cast<Render*>(_drawers[i])) {
            render->setLigths(ligths);
        }
    }

    for (uint32_t i = 0; i < _gameObjects.size(); ++i) {
        _gameObjects[i]->addLigths(ligths);
    }
}

Light* GameObject::getLigth(std::string id)
{
    Light *ligth = nullptr;

    for (uint32_t i = 0; i < _ligths.size() && !ligth; ++i) {
        if (_ligths[i]->isLigth(id)) {
            ligth = _ligths[i];
        }
    }
    return ligth;
}

std::vector<Light*> GameObject::getLigths()
{
    return this->_ligths;
}

void GameObject::scale(glm::vec3 vec3)
{
    this->_tf->_model = glm::scale(this->_tf->_model, vec3);
}

void GameObject::translate(glm::vec3 vec3)
{
    this->_tf->_model = glm::translate(this->_tf->_model, vec3);
}

void GameObject::rotate(glm::vec3 vec3, glm::quat quad)
{
    ;
}

void GameObject::rotate(glm::vec3 vec3, float angle)
{
    this->_tf->_model = glm::rotate(this->_tf->_model, angle, vec3);
}

glm::vec3 GameObject::getScale()
{
    return glm::vec3(this->_tf->_model[0].x, this->_tf->_model[1].y, this->_tf->_model[2].z);
}

float GameObject::distance(std::string id)
{
    GameObject *gameObject = search(id);

    if (!gameObject) {
        std::cerr << "The GameObject doesn't exist!" << '\n';
        throw;
    }
    return glm::distance(this->_tf->_gModel[3], gameObject->_tf->_gModel[3]);
}

std::ostream& operator<<(std::ostream& os, const GameObject& gameObject) {
    os << gameObject._id << std::endl;
    os << *gameObject._tf << std::endl;

    for (uint32_t i = 0; i < gameObject._drawers.size(); ++i) {
        if (Render *render = dynamic_cast<Render*>(gameObject._drawers[i])) {
            (void) render;
            std::cout << "Renderizable object" << '\n';
        }
    }
    return os;
}
