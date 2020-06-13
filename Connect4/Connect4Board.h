#pragma once
#include "Grid.h"

namespace Connect4
{
    enum class role
    {
        P1,
        P2
    };

    const role PLAYER1 = role::P1;
    const role PLAYER2 = role::P2;
}

class Connect4Board :
    public Grid<Connect4::role>
{
    using Grid::Grid;

public:
    bool addPiece(const size_t x, const Connect4::role &player);
    bool checkFinished() const;
    std::optional<Connect4::role> checkVictory() const;
    bool checkPlayerVictory(const Connect4::role& player) const;

private:
    bool checkHoriz(std::optional<Connect4::role>& winner) const;
    bool checkVert(std::optional<Connect4::role>& winner) const;
    bool checkDiagL(std::optional<Connect4::role>& winner) const;
    bool checkDiagR(std::optional<Connect4::role>& winner) const;
    bool checkTurnValid(const Connect4::role& player) const;
};

