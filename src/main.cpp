#include "MoveBoxes.cpp"
#include "NormalWall.cpp"
#include "SolarSystem.cpp"
#include "Airport.cpp"
#include "Engine.hpp"

void help()
{
    std::cout << "Usage: -s [Wall|Solar|Cube]" << std::endl;
}

Scene* getArgsScene(int argc, char* argv[])
{
    Scene *scene = nullptr; 
    if (argc == 3 && strncmp(argv[1], "-s", strlen(argv[1])) == 0) {
        if (strncmp(argv[2], "Wall", strlen("Wall")) == 0) {
            scene = NormalWallSim();
        } else if (strncmp(argv[2], "Cube", strlen("Cube")) == 0) {
            scene = MoveBoxesSim();
        } else if (strncmp(argv[2], "Solar", strlen("Solar")) == 0) {
            scene = SolarSystemSim();
        } else if (strncmp(argv[2], "Airport", strlen("Airport")) == 0) {
            scene = AirportSimulation();
        }
    }
    return scene;
}

int main(int argc, char* argv[]) {
    Engine *engine = nullptr;
    Scene *scene = getArgsScene(argc, argv);

    if (!scene) {
        help();
        return 1;
    }

    try { 
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
