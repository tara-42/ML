#pragma once

#include "Cube.h"



class Indexer
{
    
    public:
        Indexer();
        uint32_t getCornerIndex(Cube cube);
        uint32_t getEdgeIndex1(Cube cube);
        uint32_t getEdgeIndex2(Cube cube);
        uint64_t getEdgeIndexAll(Cube cube);

    private:

        static const int NUM_EDGES_IN_PDB = 7;

        std::array<uint8_t, (1 << Cube::NUM_EDGES)> onesArray;
        std::array<int, Cube::NUM_CORNERS> factorial;
        std::array<int, Cube::NUM_CORNERS> power3;
        std::array<int, Indexer::NUM_EDGES_IN_PDB> perms;
        std::array<int, Indexer::NUM_EDGES_IN_PDB> edgeSet1;
        std::array<int, Indexer::NUM_EDGES_IN_PDB> edgeSet2;
        std::array<int, Cube::NUM_EDGES> edgeSetAll;

        int getCornerPermRank(std::array<Cube::Cubie, Cube::NUM_CORNERS>& corners);
        int getCornerOrientRank(std::array<Cube::Cubie, Cube::NUM_CORNERS>& corners);

        template<std::size_t SIZE>
        int getEdgeOrientRank(std::array<Cube::Cubie, Cube::NUM_EDGES>& edges, std::array<int, SIZE> edgeSet);

        template<std::size_t SIZE>
        int getEdgePermRank(std::array<Cube::Cubie, Cube::NUM_EDGES>& edges, std::array<int, SIZE> edgeSet);

        std::array<uint8_t, Cube::NUM_CORNERS> getLehmerCode(Cube cube);
        int cornerLehmerToBase10(std::array<uint8_t, Cube::NUM_CORNERS>& lehmerCode);

        template<std::size_t SIZE>
        int edgeLehmerToBase10(std::array<uint8_t, SIZE>& lehmerCode);

        int fac(int n);
        int permutations(int n, int k);
};