#include <iostream>

float SquareArea(float);
float TrapezoidArea(float);
void InteractSquareArea();
void InteractTrapezoidArea();

int main()
{
   InteractSquareArea();
   std::cout << "---" << std::endl;
   InteractTrapezoidArea();
   return 0;
}


float SquareArea(float a) {
    return a * a;
}

void InteractSquareArea() {
    float aSide = 0;
    float bSide = 0;

    std::cout << "-Square area-" << std::endl;
    std::cout << "Input side: ";
    std::cin >> aSide;

    std::cout << "Rect area is " << SquareArea(aSide) << std::endl;
}

// Задача 2 Площадь трапеции
float TrapezoidArea(float a, float b, float h) {
    return ((a + b) / 2.0) * h;
}

void InteractTrapezoidArea() {
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

    std::cout << "Trapezoid area is " << TrapezoidArea(aSide, bSide, hSize) << std::endl;
}

