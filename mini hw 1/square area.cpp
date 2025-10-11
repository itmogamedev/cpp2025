#include <iostream>


int square_area(int side) {
    return side * side;
}

int main() {
    int side;
    std::cout << "Enter the side of the square: ";
    std::cin >> side;

    int area = square_area(side);
    std::cout << "Square area: " << area << std::endl;

    return 0;