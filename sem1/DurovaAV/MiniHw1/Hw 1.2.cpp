#include <iostream>

int main() 
{
    float base1, base2, height;
    std::cout << "The first base of the trapezoid? ";
    std::cin >> base1;
    std::cout << "The second base of the trapezoid? ";
    std::cin >> base2;
    std::cout << "The height of the trapezoid? ";
    std::cin >> height;
    std::cout << "The area of the trapezoid is " << (base1 + base2) * height * 0.5;
    return 0;
}
