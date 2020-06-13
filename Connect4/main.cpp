#include "Connect4Board.h"
#include <iostream>
#include "Helper.h"

int main()
{
	Connect4Board* grid = new Connect4Board(5, 5);

	Connect4::role player1, player2;

	help::displayConnect4(*grid);

	player1 = Connect4::role::P1;
	player2 = Connect4::role::P2;

	unsigned int input;

	while (!grid->checkVictory())
	{
		help::playerPrompt(player1);
		std::cin >> input;
		while (std::cin.fail() || input > grid->getWidth()) {
			std::cin.clear();
			std::cin.ignore(256, '\n');
			help::playerPrompt(player1);
			std::cin >> input;
		}
		grid->addPiece(input - 1, player1);
		help::displayConnect4(*grid);

		if (grid->checkVictory())
			break;

		help::playerPrompt(player2);
		std::cin >> input;
		while (std::cin.fail() || input > grid->getWidth()) {
			std::cin.clear();
			std::cin.ignore(256, '\n');
			help::playerPrompt(player2);
			std::cin >> input;
		}
		grid->addPiece(input - 1, player2);
		help::displayConnect4(*grid);
	}
	

	help::declareWinner(*grid);

	delete grid;
	return 0;
}