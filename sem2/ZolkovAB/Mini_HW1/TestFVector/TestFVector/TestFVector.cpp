#include <iostream>
#include "FVector.h"

int main()
{
    FVector v(3.0f, 4.0f, 0.0f);

    std::cout << "X = " << v.GetX() << std::endl;
    std::cout << "Y = " << v.GetY() << std::endl;
    std::cout << "Z = " << v.GetZ() << std::endl;
    std::cout << "Length = " << v.FLength() << std::endl;

    return 0;
}