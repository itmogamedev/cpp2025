#include <iostream>

int main()
{
	float a;

	setlocale(LC_ALL, "Rus");
	std::cout << "Введите сторону квадрата: ";
	std::cin >> a;
	if (a > 0)
	{
		std::cout << "Площадь квадрата равна: ";
		std::cout << a * a;
	}
	else
	{
		std::cout << "Невозможная сторона квадрата";
	}
}
