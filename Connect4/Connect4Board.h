#pragma once
#include "Grid.h"
//#include "Connect4TreeSearch.h"

class Connect4TreeSearch;

namespace Connect4
{
    enum class Role
    {
        P1,
        P2
    };

    const Role PLAYER1 = Role::P1;
    const Role PLAYER2 = Role::P2;

    using Board = std::vector<std::vector<Role>>;
}

class Connect4Board :
    public Grid<Connect4::Role>
{
    using Grid::Grid;


public:
    // any way to avoid using this?
    //std::vector<std::vector<std::optional<Connect4::role>>>* getBoard() const;

    size_t getBestMove();
    bool addPiece(const size_t x, const Connect4::Role &player);
    bool checkFinished() const;
    std::optional<Connect4::Role> checkVictory() const;
    bool checkPlayerVictory(const Connect4::Role& player) const;

private:
    bool checkHoriz(std::optional<Connect4::Role>& winner) const;
    bool checkVert(std::optional<Connect4::Role>& winner) const;
    bool checkDiagL(std::optional<Connect4::Role>& winner) const;
    bool checkDiagR(std::optional<Connect4::Role>& winner) const;
    bool checkTurnValid(const Connect4::Role& player) const;

    // For tree search
    int heuristicValue;
};

