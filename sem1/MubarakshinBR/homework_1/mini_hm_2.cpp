#include <iostream>

int main()
{
    float f_trap_side;
    float s_trap_side;
    float trap_h;
    std::cout << "Enter the first side of the trapezoid: ";
    std::cin >> f_trap_side;
    std::cout << "Enter the second side of the trapezoid: ";
    std::cin >> s_trap_side;
    std::cout << "Enter the height of the trapezoid: ";
    std::cin >> trap_h;
    std::cout << "The area of a trapezoid is: " << (f_trap_side + s_trap_side) / 2 * trap_h;
}