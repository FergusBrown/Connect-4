#include "Connect4Board.h"
#include <iostream>
#include "Helper.h"

int main()
{
	Connect4Board* grid = new Connect4Board(5, 5);

	Connect4::role player1 = Connect4::role::P1;
	Connect4::role player2 = Connect4::role::P2;


	char value = 22;

	grid->setItemAt(0, 0, value);

	std::optional<int> i = grid->getItemAt(0, 0);

	std::cout << i.value() << std::endl;

	grid->addPiece(0, Connect4::P1);

	i = grid->getItemAt(0, 5);

	if (i != std::nullopt)
	{
		std::cout << i.value() << std::endl;
	}

	
	help::displayConnect4(*grid);

	delete grid;
	return 0;
}