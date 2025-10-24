#include <iostream>
int main()
{
	std::cout << "Enter first base:";
	double a;
	std::cin >> a;
	std::cout << "Enter second base:";
	double b;
	std::cin >> b;
	std::cout << "Enter heigh:";
	double h;
	std::cin >> h;
	double S;
	S = ((a + b) / 2) * h;
	std::cout << "Area of trapezoid:" << S;
	return 0;
}