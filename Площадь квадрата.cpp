#include <iostream>

int find_square_area(int square_side)
{
    return square_side * square_side;
}

int main()
{
    int squareSide;
    std::cout << "Enter the side of the square: ";
    std::cin >> squareSide;
    std::cout << '\n' << "The area of the square: " << find_square_area(squareSide);
    return 0;
}