#include <iostream>
float SquareZone(float s) 
    {
        return s * s;
    }
int main() 
    {
        float s;
        std::cout << "Введите длину стороны квадрата: ";
        std::cin >> s;
        std::cout << "Площадь квадрата: " << SquareZone(s) << std::endl;
        return 0;
    }