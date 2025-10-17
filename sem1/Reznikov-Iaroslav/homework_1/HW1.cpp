#include <iostream>

float squareArea(float);
float trapezoidArea(float);
void interactSquareArea();
void interactTrapezoidArea();

int main()
{
   interactSquareArea();
   std::cout << "---" << std::endl;
   interactTrapezoidArea();
   return 0;
}


float squareArea(float a) {
    return a * a;
}

void interactSquareArea() {
    float aSide = 0;
    float bSide = 0;

    std::cout << "-Square area-" << std::endl;
    std::cout << "Input side: ";
    std::cin >> aSide;

    std::cout << "Rect area is " << squareArea(aSide) << std::endl;
}

// Задача 2 Площадь трапеции
float trapezoidArea(float a, float b, float h) {
    return ((a + b) / 2.0) * h;
}

void interactTrapezoidArea() {
    float aSide = 0;
    float bSide = 0;
    float hSize = 0;

    std::cout << "-Trapezoid area-" << std::endl;
    std::cout << "Input first basis: ";
    std::cin >> aSide;

    std::cout << "Input second basis: ";
    std::cin >> bSide;

    std::cout << "Input trapezoid height: ";
    std::cin >> hSize;

    std::cout << "Trapezoid area is " << trapezoidArea(aSide, bSide, hSize) << std::endl;
}

