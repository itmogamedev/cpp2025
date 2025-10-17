#include <iostream>

float trapezoidArea(float base1length, float base2length, float height)
{
    return (base1length + base2length) * height / 2;
}

int main() {
    float base1length, base2length, height;
    std::cout << "Enter the trapezoid first base length: ";
    std::cin >> base1length;
    std::cout << "Enter the trapezoid second base length: ";
    std::cin >> base2length;
    std::cout << "Enter the trapezoid height: ";
    std::cin >> height;
    std::cout << "Trapezoid area: " << trapezoidArea(base1length, base2length, height) << std::endl;
    return 0;
}