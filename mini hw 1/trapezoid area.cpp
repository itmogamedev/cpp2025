#include <iostream>

double Area(double base1, double base2, double height) {
    return (base1 + base2) * height / 2.0;
}

int main() {
    double base1, base2, height;

    std::cout << "Enter first base: ";
    std::cin >> base1;

    std::cout << "Enter second base: ";
    std::cin >> base2;

    std::cout << "Enter height: ";
    std::cin >> height;

    double area = Area(base1, base2, height);
    std::cout << "Area trapezoid: " << area << std::endl;

    return 0;
}
