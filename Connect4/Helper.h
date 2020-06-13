#pragma once
#include "Connect4Board.h"
#include <iostream>

namespace help
{
	void displayConnect4(const Connect4Board& board);
	void playerPrompt(const Connect4::role& player);
	void manualPlayLoop(Connect4Board& board);
	void declareWinner(const Connect4Board& board);

	const char P1_PIECE = 'X';
	const char P2_PIECE = 'O';
}

