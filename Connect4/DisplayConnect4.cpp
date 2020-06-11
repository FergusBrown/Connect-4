#pragma once
#include "Connect4Board.h"
#include <iostream>


void displayConnect4(Connect4Board &board)
{
	size_t width = board.getWidth();
	size_t height = board.getHeight();

	for (size_t i = 0; i <= width; ++i)
	{
		std::cout << "1 ";
	}
	std::cout << std::endl;

	for (size_t i = 0; i <= width; ++i)
	{
		std::cout << "_ ";
	}
	std::cout << std::endl;
}