#include <iostream>
int main()
{
	std::cout << "Square side:";
	int var;
	std::cin >> var;
	var *= var;
	std::cout << "Area of the square = ";
	std::cout << var;
	std::cout << "\nTrapezoid sides, then height:";
	float a, b, h, polusum;
	std::cin >> a, std::cin >> b, std::cin >> h;
	polusum = (a + b) / 2;
	std::cout << "Area of the trapezoid = ";
	std::cout << polusum * h;

	return 0;
}