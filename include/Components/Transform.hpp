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

    void scale(std::string vec3);
    void translate(std::string vec3);
    void rotate(std::string vec3, std::string quad);

    std::string model();

private:

    std::string _model, _gModel;

    std::string _pos, _scale;
    std::string _quat, _axis;
};

#endif // TRANSFORM_H
