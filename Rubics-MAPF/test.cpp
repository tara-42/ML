#include <iostream>
#include <queue>

#include "Cube.h"
#include "Solver2.h"

int main(int argc, char const *argv[])
{
    std::cout << "begin!" << std::endl;

    Cube cube;

    cube.applyMoves(argv[1]);

    Solver2 solver(cube);

    solver.solve();

    return 0;
}