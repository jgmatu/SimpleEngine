#include "Program/Program.hpp"

Program::Program(std::string vshader, std::string fshader) :
    _vshader(vshader),
    _fshader(fshader)
{
    std::cout << "Create program : " << _vshader << " " << _fshader << '\n';
}

Program::~Program() {
    std::cout << "Destroy program... " << '\n';
}
