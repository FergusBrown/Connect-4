#include "Connect4Board.h"
#include "DisplayConnect4.cpp"
#include <iostream>

int main()
{
	Connect4Board* grid = new Connect4Board(5, 5);

	int test = 22;

	grid->setItemAt(0, 0, test);

	std::optional<int> i = grid->getItemAt(0, 0).value();

	std::cout << i.value() << std::endl;

	grid->addPiece(1, 1);

	i = grid->getItemAt(0, 5);

	if (i != std::nullopt)
	{
		std::cout << i.value() << std::endl;
	}

	
	

	delete grid;
	return 0;
}