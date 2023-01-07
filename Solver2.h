#pragma once

#include <string>
#include "Cube.h"

class Solver2
{
    public:
        Solver2(Cube cube);
        std::string solve(void);

    private:
        Cube cube;
};