#include <iostream>

float square_area()
{
	int side = 0;

	std::cout << "Input your side: ";
	std::cin >> side;

	return side * side;
}

int main()
{
	std::cout << square_area() << std::endl;
}