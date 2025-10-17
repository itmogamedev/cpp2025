#include <iostream>
#include <locale>

double calculateSquareArea(double side_lenght) {
	return side_lenght * side_lenght;
}

double calculateTrapezoidArea(double base_a, double base_b, double height) {
	return ((base_a + base_b) / 2.0) * height;
}

int main() {
	std::setlocale(LC_ALL, "");

	double side, base_a, base_b, height;

    std::cout << "Введите сторону квадрата: ";
    std::cin >> side;
    std::cout << "Площадь квадрата = " << calculateSquareArea(side) << std::endl;

    std::cout << "\nВведите основание A трапеции: ";
    std::cin >> base_a;
    std::cout << "Введите основание B трапеции: ";
    std::cin >> base_b;
    std::cout << "Введите высоту трапеции: ";
    std::cin >> height;

    std::cout << "Площадь трапеции = " << calculateTrapezoidArea(base_a, base_b, height) << std::endl;

    return 0;
}