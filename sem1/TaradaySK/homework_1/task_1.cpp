#include <iostream>

int main()
{
    float edge;
    float square;
    std::cout << "Enter the length of the edge of the square - ";
    std::cin >> edge;
    square = edge * edge;
    std::cout << "The area of a square with an edge " << edge << ", will be equal to " << square << std::endl;
}