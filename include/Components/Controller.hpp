#include "Components/Component.hpp"
#include "Components/Camera.hpp"

#include <vector>

class Controller : public Component {

public:

    Controller();
    ~Controller();

    virtual void start();
    virtual void update();

protected:

    void changeCamera();
    std::vector<Camera*> _cameras;

private:

    void iterateCameras();
    void initCameras(std::vector<Camera*> _cameras);
    Camera* getActiveCamera();

    uint32_t _camera;

    friend class Scene;
};