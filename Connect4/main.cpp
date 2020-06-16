#include "Connect4Board.h"
#include <iostream>
#include "Helper.h"

int main()
{
	Connect4Board* board = new Connect4Board();

	help::manualPlayLoop(*board);

	delete board;
	return 0;
}