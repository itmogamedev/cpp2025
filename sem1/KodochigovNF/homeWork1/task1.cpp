#include <iostream>
#include <locale>

double calculateSquareArea(double side_length) {
    return side_length * side_length;
}

int main() {
    std::setlocale(LC_ALL, "");

    double side;
    std::cout << "Введите сторону квадрата: ";
    std::cin >> side;

    std::cout << "Площадь квадрата = " << calculateSquareArea(side) << std::endl;

    return 0;
}
