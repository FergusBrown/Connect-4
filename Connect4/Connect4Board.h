#pragma once
#include "Grid.h"
class Connect4Board :
    public Grid<int>
{

public:
    bool addPiece(const size_t x, const int player);
};

