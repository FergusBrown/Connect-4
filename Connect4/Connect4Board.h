#pragma once
#include "Grid.h"
class Connect4Board :
    public Grid<int>
{
    using Grid::Grid;

public:
    bool addPiece(const size_t x, const int player);
};

