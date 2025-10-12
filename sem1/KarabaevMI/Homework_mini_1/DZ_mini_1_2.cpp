#include <iostream>
float TrapeZone(float b1, float b2, float h) 
    {
        return ((b1 + b2) * h) / 2;
    }
int main() 
    {
        setlocale(LC_ALL, "RU");
        float b1, b2, h;
        std::cout <<"Enter the length of one of the sides of the trapezoid base: ";
        std::cin >> b1;
        std::cout <<"Enter the length of one more side of the trapezoid base: ";
        std::cin >> b2;
        std::cout <<"Enter the height of the trapezoid: ";
        std::cin >> h;
        std::cout <<"Trapezoid area: "<< TrapeZone(b1, b2, h) <<std::endl;
        return 0;
    }