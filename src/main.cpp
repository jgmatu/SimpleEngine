#include "MoveBoxes.cpp"
#include "NormalWall.cpp"
#include "SolarSystem.cpp"
#include "Engine.hpp"

int main(int argc, char* argv[]) {
    Engine *engine = nullptr;

    try {
        Scene *scene = MoveBoxesSim();
        engine = new Engine(scene);
        engine->init();
        engine->mainLoop();
    } catch (std::exception &ex) {
        std::cerr << "Engine Error : " << ex.what() << '\n';
    } catch (...) {
        std::cerr << "Engine fatal!" << '\n';
    }
    if (engine) {
        delete engine;
    }
}
