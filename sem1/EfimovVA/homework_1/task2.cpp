﻿#include <iostream>

double trapezoidArea() {
    double base1, base2, height;

    std::cout << "Write first base of trapezoid: ";
    std::cin >> base1;
    std::cout << "Write second base of trapezoid: ";
    std::cin >> base2;
    std::cout << "Write height of trapezoid: ";
    std::cin >> height;

    return (base1 + base2) * height / 2;
}

int main() {
    double area = trapezoidArea();
    std::cout << "Square of trapezoid: " << area << std::endl;
    return 0;
}