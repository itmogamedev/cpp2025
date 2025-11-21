#include <iostream>

int SquareArea(int a)
{
	return a * a;
}

int main() {
	int SquareSide;

	std::cout << "Enter the side of the square: ";
	std::cin >> SquareSide;
	std::cout << SquareArea(SquareSide);

	return 0;
}