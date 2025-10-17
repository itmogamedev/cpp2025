#include <iostream>

float squareArea(float side)
{
	return side * side;
}

int main()
{
	float side;
	std::cout << "Enter the square side length: ";
	std::cin >> side;
	std::cout << "Area of the square: " << squareArea(side) << std::endl;
	return 0;
}