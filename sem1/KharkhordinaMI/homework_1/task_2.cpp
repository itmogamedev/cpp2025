#include <iostream>

double trapeziaArea(double a, double b, double h) 
{
	return (a + b) / 2 * h;
}

int main(void) 
{
	int h, a, b;
	std::cout << "Side A: ";
	std::cin >> a;
	std::cout << "Side B: ";
	std::cin >> b;
	std::cout << "Height: ";
	std::cin >> h;
	std::cout << trapeziaArea(a, b, h) << std::endl;
}