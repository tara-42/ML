#include <bitset>
#include <array>
#include <cstdio>
#include <cmath>

#include "Indexer.h"
#include "Cube.h"

// this is number of different corner orientations there are
// it is 3^7
static constexpr const int NUM_CORNER_ORIENT_RANKS = 2187;

// this is the number of different edge orientations for 
// 7 edges. It is 2^7
static constexpr const int NUM_EDGE_ORIENT_RANKS = 128;
static constexpr const int NUM_EDGE_ORIENT_RANKS_ALL = 4096;

Indexer::Indexer()
{   
    // precompute number of 1s in integers up to 2^12
    for (int i = 0; i < (1 << Cube::NUM_EDGES); i++)
    {
        std::bitset<Cube::NUM_EDGES> bits(i);
        onesArray[i] = bits.count();
    }

    // precompute factorials
    for (int i = 0; i < Cube::NUM_CORNERS; i++)
    {
        factorial[i] = fac(i);
    }
    
    // precompute powers of 3
    power3[0] = 1;
    for (int i = 1; i < Cube::NUM_CORNERS; i++)
    {
        power3[i] = 3 * power3[i - 1];
    }

    // precompute permutations
    for (int i = 0; i < Indexer::NUM_EDGES_IN_PDB; i++)
    {
        perms[i] = permutations(Cube::NUM_EDGES - i - 1, Indexer::NUM_EDGES_IN_PDB - i - 1);
    }
 
}

uint32_t Indexer::getCornerIndex(Cube cube)
{
    std::array<Cube::Cubie, Cube::NUM_CORNERS>& corners = cube.getCorners();

    return (getCornerPermRank(corners) * NUM_CORNER_ORIENT_RANKS) + getCornerOrientRank(corners);
}

uint32_t Indexer::getEdgeIndex1(Cube cube)
{
    std::array<Cube::Cubie, Cube::NUM_EDGES>& edges = cube.getEdges();

    int found = 0;
    for (int i = 0; i < Cube::NUM_EDGES; i++)
    {
        if (edges[i].index < Indexer::NUM_EDGES_IN_PDB)
        {
            edgeSet1[edges[i].index] = i;
            found++;
        }
        if (found == Indexer::NUM_EDGES_IN_PDB) { break; }
    }

    return (getEdgePermRank(edges, edgeSet1) * NUM_EDGE_ORIENT_RANKS)
     + getEdgeOrientRank(edges, edgeSet1);
}

uint32_t Indexer::getEdgeIndex2(Cube cube)
{
    std::array<Cube::Cubie, Cube::NUM_EDGES>& edges = cube.getEdges();

    int found = 0;
    for (int i = 0; i < Cube::NUM_EDGES; i++)
    {
        if (edges[i].index >= 5)
        {
            edgeSet2[edges[i].index - 5] = i;
            found++;
        }
        if (found == Indexer::NUM_EDGES_IN_PDB) { break; }
    }

    return (getEdgePermRank(edges, edgeSet2) * NUM_EDGE_ORIENT_RANKS)
     + getEdgeOrientRank(edges, edgeSet2);
}

// this is a bit of a hack. Returns a 64 bit int that
// has the 32 bits from first edge group and 32 from second
uint64_t Indexer::getEdgeIndexAll(Cube cube)
{
    return ((uint64_t)getEdgeIndex1(cube) << 32) | getEdgeIndex2(cube);
}

template<std::size_t SIZE>
int Indexer::getEdgeOrientRank(std::array<Cube::Cubie, Cube::NUM_EDGES>& edges, std::array<int, SIZE> edgeSet)
{
    int res = 0;
    int counter = 0;

    for (int index : edgeSet)
    {
        res |= edges[index].orientation << counter;
        counter++;
    }

    return res;
}

template<std::size_t SIZE>
int Indexer::getEdgePermRank(std::array<Cube::Cubie, Cube::NUM_EDGES>& edges, std::array<int, SIZE> edgeSet)
{   
    // since the last number of code is always 0
    // could probably just make this NUM_CORNERS - 1 size for speed
    std::array<uint8_t, SIZE> lehmerCode;
    std::bitset<Cube::NUM_EDGES> bits;
    
    // first value of code is always first value of permutation
    lehmerCode[0] = edgeSet[0];
    bits.set(Cube::NUM_EDGES - edgeSet[0] - 1);

    // last value of code always 0 NOT ALWAYS TRUE FOR PARTIAL!
    // lehmerCode[Indexer::NUM_EDGES_IN_PDB - 1] = 0;
    int counter = 1;
    for (int i = 1; i < (int)SIZE; i++)
    {
        bits.set(Cube::NUM_EDGES - edgeSet[i] - 1);
        lehmerCode[counter] = edgeSet[i] - onesArray[bits.to_ulong() >> (Cube::NUM_EDGES - edgeSet[i])];
        counter++;
    }

    return edgeLehmerToBase10(lehmerCode);
}

int Indexer::getCornerOrientRank(std::array<Cube::Cubie, Cube::NUM_CORNERS>& corners)
{
    int res = 0;

    // -1 because orientation of 7 corners determines the 8th.
    // A single corner cannot be rotated on the Rubiks cube
    for (int i = 0; i < Cube::NUM_CORNERS - 1; i++)
    {   
        res += corners[Cube::NUM_CORNERS - i - 2].orientation * power3[i];
    }

    return res;
}


int Indexer::getCornerPermRank(std::array<Cube::Cubie, Cube::NUM_CORNERS>& corners)
{

    // since the last number of code is always 0
    // could probably just make this NUM_CORNERS - 1 size for speed
    std::array<uint8_t, Cube::NUM_CORNERS> lehmerCode;
    std::bitset<Cube::NUM_CORNERS> bits;
    
    // first value of code is always first value of permutation
    lehmerCode[0] = corners[0].index;
    bits.set(Cube::NUM_CORNERS - corners[0].index - 1);

    // last value of code always 0
    lehmerCode[Cube::NUM_CORNERS - 1] = 0;

    for (int i = 1; i <= Cube::NUM_CORNERS - 2; i++){

        bits.set(Cube::NUM_CORNERS - corners[i].index - 1);
        lehmerCode[i] = corners[i].index - onesArray[bits.to_ulong() >> (Cube::NUM_CORNERS - corners[i].index)];
    }

    return cornerLehmerToBase10(lehmerCode);
}


int Indexer::cornerLehmerToBase10(std::array<uint8_t, Cube::NUM_CORNERS>& lehmerCode)
{
    int res = 0;

    for (int i = 0; i < Cube::NUM_CORNERS; i++)
    {
        res += lehmerCode[Cube::NUM_CORNERS - i - 1] * factorial[i];
    }

    return res;
}

template<std::size_t SIZE>
int Indexer::edgeLehmerToBase10(std::array<uint8_t, SIZE>& lehmerCode)
{
    int res = 0;
    for (int i = 0; i < (int)SIZE; i++)
    {
        res += lehmerCode[i] * perms[i];
    }
    return res;
}

int Indexer::permutations(int n, int k)
{
    return fac(n) / fac(n - k);
}


int Indexer::fac(int n){
    if (n == 0 || n == 1) { return 1; }
    else return n * fac(n - 1);
}
