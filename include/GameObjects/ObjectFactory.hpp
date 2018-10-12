#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <iostream>
#include <string>

class ObjectFactory {

public:

    ObjectFactory();
    ~ObjectFactory();

private:

    std::vector<GameObject*> _GameObjects;

};

#endif // OBJECT_FACTORY_H
