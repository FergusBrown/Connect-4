#include "Connect4Board.h"
#include <iostream>
#include "Helper.h"

int main()
{
	Connect4Board* grid = new Connect4Board(5, 5);

	Connect4::role player1, player2;

	player1 = Connect4::role::P1;
	player2 = Connect4::role::P2;


	char value = 22;

	grid->setItemAt(0, 0, player1);

	std::optional<Connect4::role> i = grid->getItemAt(0, 0);

	grid->addPiece(0, player1);
	
	help::displayConnect4(*grid);

	delete grid;
	return 0;
}