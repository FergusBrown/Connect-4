#include "Grid.h"
#include <iostream>

int main()
{
	Grid<int>* grid = new Grid<int>(5, 5);

	int test = 22;

	grid->setItemAt(0, 0, test);

	int i = grid->getItemAt(0, 0).value();

	std::cout << i << std::endl;

	delete grid;
	return 0;
}