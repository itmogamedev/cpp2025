#include <iostream>

int main()
{
    float base_top;
    float base_bottom;
    float hight;
    float trapezoid;
    std::cout << "Enter the length of the top trapezoid base - ";
    std::cin >> base_top;
    std::cout << "Enter the length of the bottom trapezoid base - ";
    std::cin >> base_bottom;
    std::cout << "Enter the hight of the trapezoid - ";
    std::cin >> hight;
    trapezoid = ((base_bottom+base_top)/2)*hight;
    std::cout << "The area of a trapezoid with bases " << base_top<<", "<<base_bottom<<" and hight "<<hight << ", will be equal to " << trapezoid;
    

}