#include <iostream>

float TrapArea(float base1, float base2, float hight) {
	return ((base1 + base2) * hight) / 2;
}

int main() {
	setlocale(LC_ALL, "RU");
	float base1, base2, hight;
	std::cout << "Enter the first base of trapezoid: ";
	std::cin >> base1;

	std::cout << "Enter the second base of trapezoid: ";
	std::cin >> base2;

	std::cout << "Enter the hight of trapezoid: ";
	std::cin >> hight;

	std::cout << "Trapezoid area: " << TrapArea(base1, base2, hight) << std::endl;

	return 0;
}