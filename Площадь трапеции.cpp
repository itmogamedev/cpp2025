#include <iostream>

float find_trapezoid_area(float trapezoid_base1, float trapezoid_base2, float trapezoid_height)
{
    return (trapezoid_base1 + trapezoid_base2) * trapezoid_height / 2;
}

int main()
{
    float trapezoidBase1, trapezoidBase2, trapezoidHeight;
    std::cout << "Enter bases of the trapezoid: ";
    std::cin >> trapezoidBase1 >> trapezoidBase2;
    std::cout << '\n' << "Enter the height of the trapezoid: ";
    std::cin >> trapezoidHeight;
    std::cout << '\n' << "The area of the trapezoid: " << find_trapezoid_area(trapezoidBase1, trapezoidBase2, trapezoidHeight);
    return 0;
}