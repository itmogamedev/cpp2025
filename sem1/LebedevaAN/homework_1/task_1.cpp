#include <iostream>

double getSquareArea(double square_side) {
    return square_side * square_side;
}

int main() {
    double square_side;
    std::cout << "Enter the square's side value to get its area\n";
    std::cin >> square_side;
    std::cout << getSquareArea(square_side) << std::endl;
}
