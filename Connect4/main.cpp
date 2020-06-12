#include "Connect4Board.h"
#include <iostream>
#include "Helper.h"

int main()
{
	Connect4Board* grid = new Connect4Board(5, 5);

	Connect4::role player1, player2;

	player1 = Connect4::role::P1;
	player2 = Connect4::role::P2;

	//grid->addPiece(4, player1);
	grid->addPiece(3, player1);
	grid->addPiece(3, player1);
	grid->addPiece(1, player1);
	grid->addPiece(1, player2);
	grid->addPiece(1, player2);
	grid->addPiece(1, player1);

	grid->addPiece(2, player2);
	grid->addPiece(2, player2);
	grid->addPiece(2, player1);
	
	help::displayConnect4(*grid);


	if (grid->checkVictory() == std::nullopt) {
		std::cout << "Nobody has won yet" << std::endl;
	}
	else {
		switch (grid->checkVictory().value())
		{
		case Connect4::role::P1:
			std::cout << "P1 Wins" << std::endl;
			break;
		case Connect4::role::P2:
			std::cout << "P2 Wins" << std::endl;
			break;
		}
	}

	delete grid;
	return 0;
}