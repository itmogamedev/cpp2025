#include <iostream>

int main() {
    double side1;
    double side2;
    double height;
    std::cout << "Введите длину первого основания" << std::endl;
    std::cin >> side1;
    std::cout << "Введите длину второго основания" << std::endl;
    std::cin >> side2;
    std::cout << "Введите длину высоты" << std::endl;
    std::cin >> height;
    std :: cout << "Площадь трапеции = " << ((side1+side2)/2)*height;
    return 0;
}