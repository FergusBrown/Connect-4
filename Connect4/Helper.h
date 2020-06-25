#pragma once
#include "Connect4Board.h"
#include <iostream>

namespace help
{
	// Run game
	void manualPlayLoop(Connect4Board& board);
	void agentLoopP2(Connect4Board& board);

	// Utility
	// - Generic
	void displayConnect4(const Connect4Board& board);
	void playerPrompt(const Connect4::Role& player);
	void declareWinner(const Connect4Board& board);

	const char P1_PIECE = 'X';
	const char P2_PIECE = 'O';

	// - AI
	void agentTypePrompt();
	int getMinimaxDepth();
	int getMCTSDuration();
	int getAgentType();
	int getAgentParameter(int agentSelect);

	
}

