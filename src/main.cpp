#include <iostream>
#include <exception>

#include "GameObjects/ObjectFactory.hpp"
#include "Systems/Draw.hpp"
#include "Systems/Update.hpp"
#include "Systems/IO.hpp"

#include "Engine.hpp"


int main(int argc, char* argv[]) {
    ObjectFactory *objectFactory = nullptr;
    Engine *engine = nullptr;

    try {
        objectFactory = new ObjectFactory();
        objectFactory->generateDemoObjects();
        engine = new Engine(objectFactory);
        engine->add(new Update());
        engine->add(new Draw());
        engine->add(new IO());
        engine->init();
        engine->mainLoop();
    } catch (std::exception &ex) {
        std::cerr << "Engine Error : " << ex.what() << '\n';
    } catch (...) {
        std::cerr << "Engine fatal!" << '\n';
    }
    delete engine;
}
