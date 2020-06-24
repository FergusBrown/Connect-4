#pragma once
#include "Grid.h"
#include "TreeNode.h"
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

    // win score for MCTS
    const size_t WIN_SCORE = 2;
    const size_t DRAW_SCORE = 1;
}

class Connect4Board :
    public Grid<Connect4::Role>
{

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
    size_t getBestMove(const int searchType, const int maxDepth) const;
    

private:
    // Victory checking
    bool checkHoriz(std::optional<Connect4::Role>& winner) const;
    bool checkVert(std::optional<Connect4::Role>& winner) const;
    bool checkDiagL(std::optional<Connect4::Role>& winner) const;
    bool checkDiagR(std::optional<Connect4::Role>& winner) const;
    bool checkDraw() const;
    bool inProgress() const;

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
    size_t monteCarloSearch(const long maxTime) const;

    // - Heuristic evaluation
    int evaluateBoard(const Connect4::Role player) const;
    int featureTwo(const Connect4::Role player, const size_t horiz, const size_t vert, const size_t diagL, const size_t diagR, const size_t max) const;
    int featureThree(const Connect4::Role player) const;
    int featureFour(const Connect4::Role player) const;

    // - MCTS functions
    TreeNode<Connect4Board>* selectNode(TreeNode<Connect4Board>* rootNode) const;
    void expandNode(TreeNode<Connect4Board>* node) const;
    int simulatePlayout(const TreeNode<Connect4Board>* node, const Connect4::Role& optimisingPlayer) const;
    void backPropagate(TreeNode<Connect4Board>* node, int playoutResult) const;
    size_t getBestMCTSScore(TreeNode<Connect4Board>* node) const;   // Why can node pointer not be const

};

