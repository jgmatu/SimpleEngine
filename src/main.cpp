#include <iostream>
#include <exception>

#include "GameObjects/ObjectFactory.hpp"
#include "Engine.hpp"

int main(int argc, char* argv[]) {
    ObjectFactory *objectFactory = new ObjectFactory();
    objectFactory->generateDemoObjects();

    Engine *engine = new Engine(objectFactory);

    try {
        engine->init();
        engine->mainLoop();
    } catch (std::exception &ex) {
        std::cerr << ex.what() << '\n';
    } catch (...) {
        std::cerr << "Engine fatal!" << '\n';
    }
    delete engine;
}
