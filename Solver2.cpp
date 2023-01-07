#include <string>
#include <queue>
#include <array>
#include <vector>
#include <iostream>
#include <set>

#include "Solver2.h"


Solver2::Solver2(Cube cube)
{
    this->cube = cube;
}

std::string Solver2::solve(void)
{
    std::queue<Cube> open;
    std::vector<Cube> neighbours;

    open.push(this->cube);

    int expanded = 0;

    while (!open.empty()){
        Cube current = open.front();
        open.pop();

        printf("expanding node %d\n", expanded);
        expanded++;

        if (current.isCornerSolved()) 
        {
            std::cout << "SOLUTION FOUND!" << std::endl;
            return "solution";
        }

        neighbours = current.generateNeighbours2();

        for (Cube neighbour : neighbours)
        {
            if (neighbour.isCornerSolved()){
                std::cout << "SOLUTION FOUND!" << std::endl;
                return "solution"; 
            }
            else
            {
                open.push(neighbour);
            }
        }
    }

    return "not implemented";
}

