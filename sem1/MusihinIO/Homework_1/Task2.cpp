#include <iostream>

float TrapezoidArea(float a, float b, float h)
{
	return (a + b) / 2 * h;
}

int main() {
	float TrapezoidSide1;
	float TrapezoidSide2;
	float TrapezoidHeight;

	std::cout << "Enter the top side of the trapezoid: ";
	std::cin >> TrapezoidSide1;
	std::cout << "Enter the bottom side of the trapezoid: ";
	std::cin >> TrapezoidSide2;
	std::cout << "Enter the height: ";
	std::cin >> TrapezoidHeight;
	std::cout << TrapezoidArea(TrapezoidSide1, TrapezoidSide2, TrapezoidHeight);

	return 0;
}