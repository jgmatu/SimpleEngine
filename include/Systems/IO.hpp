#ifndef SYSTEM_IO_H
#define SYSTEM_IO_H

#include <vector>
#include <iostream>
#include <string>
#include <memory>

#include "Systems/System.hpp"
#include "Messages/Message.hpp"

class IO : public System {

public:

     IO();
    ~IO();

    void init(Scene *scene);
    void update(float dt, Scene *scene);
    void sendMessage (Message *msg);

};

#endif // SYSTEM_IO_H
