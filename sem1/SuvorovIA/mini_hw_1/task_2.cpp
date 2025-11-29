﻿#include <iostream>

float trapezoid_area()
{
	float side_1 = 0;
	float side_2 = 0;
	float height = 0;
	float area = 0;

	std::cout << "Input your 1 side: ";
	std::cin >> side_1;

	std::cout << "Input your 2 side: ";
	std::cin >> side_2;

	std::cout << "Input your height: ";
	std::cin >> height;

	area = (side_1 + side_2) / 2 * height;
	return area;
}

int main()
{
	std::cout << trapezoid_area() << std::endl;
}