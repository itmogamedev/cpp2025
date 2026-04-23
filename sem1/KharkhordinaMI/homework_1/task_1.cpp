#include <iostream>

double square(double side)
{
	return side * side;
}

int main()
{
	double side;
	std::cout << "length side: ";
	std::cin >> side;

	double area = square(side);
	std::cout << "area = " << area << std::endl;
	return 0;

}