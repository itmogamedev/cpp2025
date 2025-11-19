#include <iostream>

float getSquareArea(float side)
{
    return side * side;
}

void SquareArea()
{
    float side;
    std::cout << "Enter square side length: ";
    std::cin >> side;
    std::cout << "Square area: " << getSquareArea(side);
}

float getTrapezoidArea(float larger_base, float smaller_base, float height)
{
    return 0.5 * (larger_base + smaller_base) * height;
}

void TrapezoidArea()
{
    float larger_base;
    float smaller_base;
    float height;
    std::cout << "Enter larger base length: ";
    std::cin >> larger_base;
    std::cout << "Enter smaller base length: ";
    std::cin >> smaller_base;
    std::cout << "Enter height length: ";
    std::cin >> height;
    std::cout << "Trapezoid area: " << getTrapezoidArea(larger_base, smaller_base, height);
}

int main(void)
{
    int option;
    bool selected = false;

    while (!selected)
    {
        std::cout << "Select task:\n\t- [1] Square area\n\t- [2] Trapezoid area\n(1-2): ";
        std::cin >> option;
        if (option == 1)
        {
            SquareArea();
            selected = true;
        }
        else if (option == 2)
        {
            TrapezoidArea();
            selected = true;
        }
        else
        {
            std::cout << "Wrong option\n";
            selected = false;
        }
    }

    return 1;
}