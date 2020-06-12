#pragma once
#include "Connect4Board.h"
#include <iostream>

namespace help
{
	void displayConnect4(Connect4Board& board);
	void playerPrompt(Connect4::role& player);

	const char P1_PIECE = 'X';
	const char P2_PIECE = 'O';
}

