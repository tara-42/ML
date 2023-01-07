//    * Edge indices.
//    *
//    * 0  1  2  3  4  5  6  7  8  9  10 11
//    * UB UR UF UL FR FL BL BR DF DL DB DR
//    * BO BY BR BW RY RW OW OY GR GW GO GY
//    *
//    * Corner indices.
//    *
//    * 0   1   2   3   4   5   6   7
//    * ULB URB URF ULF DLF DLB DRB DRF
//    * BWO BOY BYR BRW GWR GOW GYO GRY

// Cube is configured in orientation with blue up, red front


#pragma once

#include <cstdint>
#include <array>
#include <vector>

class Cube
{
    public:

        static const int NUM_CORNERS = 8;
        static const int NUM_EDGES = 12;

        bool operator==(const Cube &cube) const
        {
            return (this->edges == cube.edges) && (this->corners == cube.corners);
        }

        enum move
        {
            NONE,
            R,
            R_PRIME,
            R2,
            U,
            U_PRIME,
            U2,
            F,
            F_PRIME,
            F2,
            D,
            D_PRIME,
            D2,
            B,
            B_PRIME,
            B2,
            L,
            L_PRIME,
            L2
        };

        enum layer
        {
            UP, DOWN, LEFT, RIGHT
        };
        
        struct Cubie
        {
            uint8_t index;
            uint8_t orientation;

            bool operator==(const Cubie &cubie) const
            {
                return (this->index == cubie.index) && (this->orientation == cubie.orientation);
            }

        };



        Cube();
        bool isSolved(void);
        bool isEdgeSolved(void);
        bool isCornerSolved(void);

        void printCubeState(void);
        void applyMoves(std::string moveList);

        std::vector<Cube> generateNeighbours2(void);
        std::vector<Cube> generateNeighbours(void);
        std::vector<Cube> generateNeighboursPruned(void);
        std::array<Cubie, Cube::NUM_CORNERS>& getCorners(void);
        std::array<Cubie, Cube::NUM_EDGES>& getEdges(void);

        uint8_t getDepth(void);

        void r();
        void rPrime();
        void r2();

        void u();
        void uPrime();
        void u2();

        void f();
        void fPrime();
        void f2();

        void d();
        void dPrime();
        void d2();

        void l();
        void lPrime();
        void l2();

        void b();
        void bPrime();
        void b2();


    private:

        std::array<Cubie, 12> edges;
        std::array<Cubie, 8> corners;
        move lastMove;
        uint8_t depth;

        void updateCornerOrientation(uint8_t corner_index, uint8_t change);
        void flipEdgeOrientation(uint8_t edge_index);

        void swapCornerCubies(uint8_t first_index, uint8_t second_index);
        void swapEdgeCubies(uint8_t first_index, uint8_t second_index);

        void fourCycleCorners(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4);
        void fourCycleEdges(uint8_t e1, uint8_t e2, uint8_t e3, uint8_t e4);
};