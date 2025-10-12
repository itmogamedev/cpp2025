#include <iostream>
float TrapeZone(float b1, float b2, float h) 
    {
        return ((b1 + b2) * h) / 2;
    }
int main() 
    {
        setlocale(LC_ALL, "RU");
        float b1, b2, h;
        std::cout <<"Введите длину одной из сторон основания трапеции: ";
        std::cin >> b1;
        std::cout <<"Введите длину еще одной стороны основания трапеции: ";
        std::cin >> b2;
        std::cout <<"Введите высоту трапеции: ";
        std::cin >> h;
        std::cout <<"Площадь трапеции: "<< TrapeZone(b1, b2, h) <<std::endl;
        return 0;
    }