#include <unordered_set>
#include <queue>
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

#include "PDBBuilder.h"
#include "Cube.h"
#include "Indexer.h"

PDBBuilder::PDBBuilder()
{
}


void PDBBuilder::buildCorners(void)
{
    Indexer indexer;

    std::unordered_set<int32_t> closed;
    std::queue<Cube> open;
    std::vector<Cube> neighbours;
    std::array<uint8_t, NUM_CORNER_RANKS>* database = new std::array<uint8_t, NUM_CORNER_RANKS>{0};

    Cube cube;
    open.push(cube);
    closed.insert(0);

    while (!open.empty()){
        Cube current = open.front();
        open.pop();
        
        uint32_t rank = indexer.getCornerIndex(current);
        uint32_t databaseVal = (*database)[rank];
        if (databaseVal == 0 || databaseVal > current.getDepth())
        {
            (*database)[rank] = current.getDepth();
        }

        neighbours = current.generateNeighbours();

        for (Cube neighbour : neighbours)
        {
            uint32_t neighbourRank = indexer.getCornerIndex(neighbour);

            // only push neighbours if not visited
            // and it's less than 12 moves in
            if (!closed.count(neighbourRank) && neighbour.getDepth() <= MAX_DEPTH)
            {
                open.push(neighbour);
                closed.insert(neighbourRank);
            }
        }
    }

    std::ofstream writer("cornerDB.data", std::ios::out | std::ios::binary | std::ios::trunc);
    writer.write((char*)database, sizeof(uint8_t) * NUM_CORNER_RANKS);
    writer.close();

    delete[] database;
}

void PDBBuilder::buildEdges1(void)
{
    Indexer indexer;
    std::array<uint8_t, NUM_EDGE_RANKS>* database = new std::array<uint8_t, NUM_EDGE_RANKS>{0};

    for (uint8_t currDepth = 0; currDepth <= 10; currDepth++)
    {
        DFS(indexer, currDepth, database);
    }

    // all database values not filled in must be 11 moves
    for (int i = 0; i < NUM_EDGE_RANKS; i++)
    {
        if ((*database)[i] == 0)
        {
            (*database)[i] = 11;
        }
    }

    // add 0 for solved cube, since it's overwritten
    Cube cube;
    (*database)[indexer.getEdgeIndex1(cube)] = 0;


    std::ofstream writer("edge1DB safety.data", std::ios::out | std::ios::binary | std::ios::trunc);
    writer.write((char*)database, sizeof(uint8_t) * NUM_EDGE_RANKS);
    writer.close();

    delete[] database;
}

void PDBBuilder::buildEdges2(void)
{
    Indexer indexer;
    std::array<uint8_t, NUM_EDGE_RANKS>* database = new std::array<uint8_t, NUM_EDGE_RANKS>{0};

    for (uint8_t currDepth = 0; currDepth <= 10; currDepth++)
    {
        DFS2(indexer, currDepth, database);
    }

    // all database values not filled in must be 11 moves
    for (int i = 0; i < NUM_EDGE_RANKS; i++)
    {
        if ((*database)[i] == 0)
        {
            (*database)[i] = 11;
        }
    }

    // add 0 for solved cube, since it's overwritten
    Cube cube;
    (*database)[indexer.getEdgeIndex2(cube)] = 0;

    std::ofstream writer("edge2DB safety.data", std::ios::out | std::ios::binary | std::ios::trunc);
    writer.write((char*)database, sizeof(uint8_t) * NUM_EDGE_RANKS);
    writer.close();

    delete[] database;
}

std::array<uint8_t, PDBBuilder::NUM_EDGE_RANKS>* PDBBuilder::testDFS(int depth)
{
    Indexer indexer;
    std::array<uint8_t, NUM_EDGE_RANKS>* database = new std::array<uint8_t, NUM_EDGE_RANKS>{0};

    for (uint8_t currDepth = 0; currDepth <= depth; currDepth++)
    {
        DFS(indexer, currDepth, database);
    }

    // all database values not filled in must be 11 moves
    for (int i = 0; i < NUM_EDGE_RANKS; i++)
    {
        if ((*database)[i] == 0)
        {
            (*database)[i] = 11;
        }
    }

    // add 0 for solved cube, since it's overwritten
    Cube cube;
    (*database)[indexer.getEdgeIndex1(cube)] = 0;


    return database;
}


void PDBBuilder::DFS(Indexer indexer, uint8_t maxDepth, std::array<uint8_t, NUM_EDGE_RANKS>* database)
{
    std::cout << "~~~~~~~~~~~~STARTING DEPTH " << (int)maxDepth << std::endl;

    std::stack<Cube> open;
    std::vector<Cube> neighbours;

    Cube cube;
    open.push(cube);

    int counter = 0;
    int populated = 0;

    while (!open.empty()){
        Cube current = open.top();
        open.pop();

        if (counter & 8388608)
        {
            std::cout << "open size: " << open.size() << std::endl;
            std::cout << "populated: " << populated << std::endl;
            std::cout << "depth: " << (int)maxDepth << std::endl;
            counter = 0;
        }
        counter++;
        
        uint32_t rank = indexer.getEdgeIndex1(current);
        uint32_t databaseVal = (*database)[rank];

        if (databaseVal == 0)
        {
            populated++;
            (*database)[rank] = current.getDepth();
        }
        
        // dont generate neighbours if max depth is reached
        // or database already has entry
        if (current.getDepth() == maxDepth || databaseVal < current.getDepth())
        {
            continue;
        }

        neighbours = current.generateNeighbours();

        for (Cube neighbour : neighbours)
        {
            open.push(neighbour);
        }
    }

    std::cout << "Searched depth: " << (int)maxDepth << std::endl;
    std::cout << "Database entries filled: " << populated << std::endl;
}



std::array<uint8_t, PDBBuilder::NUM_CORNER_RANKS>* PDBBuilder::getCornerPDB()
{   

    std::array<uint8_t, NUM_CORNER_RANKS>* database = new std::array<uint8_t, NUM_CORNER_RANKS>{0};

    std::ifstream reader("cornerDB do not edit.data", std::ios::in);

    if (!reader.is_open())
    {
        throw std::exception();
    }

    reader.seekg(0, std::ios::beg);
    reader.read(
      (char*)database,
      sizeof(uint8_t) * NUM_CORNER_RANKS);
    reader.close();

    return database;
}

void PDBBuilder::DFS2(Indexer indexer, uint8_t maxDepth, std::array<uint8_t, NUM_EDGE_RANKS>* database)
{
    std::cout << "~~~~~~~~~~~~STARTING DEPTH " << (int)maxDepth << std::endl;

    std::stack<Cube> open;
    std::vector<Cube> neighbours;

    Cube cube;
    open.push(cube);

    int counter = 0;
    int populated = 0;

    while (!open.empty()){
        Cube current = open.top();
        open.pop();

        if (counter & 8388608)
        {
            std::cout << "open size: " << open.size() << std::endl;
            std::cout << "populated: " << populated << std::endl;
            std::cout << "depth: " << (int)maxDepth << std::endl;
            counter = 0;
        }
        counter++;
        
        uint32_t rank = indexer.getEdgeIndex2(current);
        uint32_t databaseVal = (*database)[rank];

        if (databaseVal == 0)
        {
            populated++;
            (*database)[rank] = current.getDepth();
        }
        
        // dont generate neighbours if max depth is reached
        // or database already has entry
        if (current.getDepth() == maxDepth || databaseVal < current.getDepth())
        {
            continue;
        }

        neighbours = current.generateNeighbours();

        for (Cube neighbour : neighbours)
        {
            open.push(neighbour);
        }
    }

    std::cout << "Searched depth: " << (int)maxDepth << std::endl;
    std::cout << "Database entries filled: " << populated << std::endl;
}


std::array<uint8_t, PDBBuilder::NUM_EDGE_RANKS>* PDBBuilder::getEdgePDB(std::string filename)
{   

    std::array<uint8_t, NUM_EDGE_RANKS>* database = new std::array<uint8_t, NUM_EDGE_RANKS>{0};

    std::ifstream reader(filename, std::ios::in);

    if (!reader.is_open())
    {
        throw std::exception();
    }

    reader.seekg(0, std::ios::beg);
    reader.read(
      (char*)database,
      sizeof(uint8_t) * NUM_EDGE_RANKS);
    reader.close();

    return database;
}