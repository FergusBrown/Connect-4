#pragma once
#include "Grid.h"
#include <stack>

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
    //using Grid::Grid();


public:
    // Constructors
    Connect4Board();

    // Player utility
    bool addPiece(const size_t x, const Connect4::Role& player);
    bool checkFinished() const;
    std::optional<Connect4::Role> checkVictory() const;
    bool checkPlayerVictory(const Connect4::Role& player) const;
    std::stack<size_t> getMoveHistory();

    Connect4::Role checkPlayerTurn() const;
    bool rollBackMove();

    // AI
    size_t getBestMove(const int maxDepth) const;
    

private:
    // Victory checking
    bool checkHoriz(std::optional<Connect4::Role>& winner) const;
    bool checkVert(std::optional<Connect4::Role>& winner) const;
    bool checkDiagL(std::optional<Connect4::Role>& winner) const;
    bool checkDiagR(std::optional<Connect4::Role>& winner) const;
    bool checkDraw() const;

    // Count number of connections
    size_t maxConnections(const Connect4::Role& player) const;
    size_t countHoriz(const Connect4::Role& player) const;
    size_t countVert(const Connect4::Role& player) const;
    size_t countDiagL(const Connect4::Role& player) const;
    size_t countDiagR(const Connect4::Role& player) const;

    // Turn validation
    bool checkTurnValid(const Connect4::Role& player) const;

    // List of move made
    std::stack<size_t> moveHistory;

    // Members for AI/tree search
    size_t depthFirstSearch(const size_t maxDepth) const;
    size_t alphaBetaSearch(const size_t maxDepth) const;

    // - Heuristic evaluation
    int evaluateBoard(const Connect4::Role player) const;
    int featureTwo(const Connect4::Role player, const size_t horiz, const size_t vert, const size_t diagL, const size_t diagR, const size_t max) const;
    int featureThree(const Connect4::Role player) const;
    int featureFour(const Connect4::Role player) const;
};

