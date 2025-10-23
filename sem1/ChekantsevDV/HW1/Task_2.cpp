#include <iostream>

int main()
{
    float a, b, h;
    setlocale(LC_ALL, "Rus");
    std::cout << "Введите длину первого основания трапеции: ";
    std::cin >> a;
    std::cout << "Введите длину второго основания трапеции: ";
    std::cin >> b;
    std::cout << "Введите длину высоты трапеции: ";
    std::cin >> h;
    if (a * b * h > 0)
    {
        std::cout << "Площадь трапеции равна: " << (a + b) / 2 * h << std::endl;
    }
    else
    {
        std::cout << "Введена(ы) неверное(ые) значение(я)";
    }
}   

    
