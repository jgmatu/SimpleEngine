#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>
#include <string>

#include "Components/Component.hpp"

class Transform : public Component {

public:

    Transform();
    ~Transform();

    void start();
    void awakeStart();
    void update();

private:

    std::string _model, _gModel;
    std::string _pos, _scale;
    std::string _quat, _axis;

};

#endif // TRANSFORM_H
