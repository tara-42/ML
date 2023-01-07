#pragma once

/* ideas:

iterate through ~420M states that are 11 moves or fewer from solved

for every unique state, add 24 entries to the PDB for 24 symmetries


*/

#include "Indexer.h"

class PDBBuilder
{
    public:
        static const int NUM_CORNER_RANKS = 88179840;
        static const int NUM_EDGE_RANKS = 510935040;

        static void buildCorners(void);
        static void buildEdges1(void);
        static void buildEdges2(void);

        static std::array<uint8_t, NUM_CORNER_RANKS>* getCornerPDB();
        static std::array<uint8_t, NUM_EDGE_RANKS>* getEdgePDB(std::string filename);

        static std::array<uint8_t, NUM_EDGE_RANKS>* testDFS(int depth);

    private:
        PDBBuilder();
        static const int MAX_DEPTH = 11;
        static void DFS(Indexer indexer, uint8_t maxDepth, std::array<uint8_t, NUM_EDGE_RANKS>* database);
        static void DFS2(Indexer indexer, uint8_t maxDepth, std::array<uint8_t, NUM_EDGE_RANKS>* database);
};