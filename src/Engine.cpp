#include "Engine.hpp"

Engine::Engine() {
    std::cout << "Open openGL Glad Context..." << '\n';
    std::cout << "Init windows system glfws..." << '\n';
}


Engine::~Engine() {
    std::cout << "Exit system windows..." << '\n';
    std::cout << "Close openGL Glad Context" << '\n';
}
