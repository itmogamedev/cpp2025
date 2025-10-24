#include <iostream>

int main()
{
    float side1, side2, height;
    std::cout << "Введите первое основание трапеции" << std::endl;
    std::cin >> side1;
    std::cout << "Ведите второе основание трапеции" << std::endl;
    std::cin >> side2;
    std::cout << "Введите высоту трапеции" << std::endl;
    std::cin >> height;
    std::cout << "Площадь трапеции равна " << (side1 + side2) / 2 * height << std::endl;

    return 0;
}