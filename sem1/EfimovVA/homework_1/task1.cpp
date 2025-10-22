#include <iostream>

double getSquareArea() {
    double side;
    std::cout << "Write a side of square: ";
    std::cin >> side;
    return side * side;
}

int main() {
    double area = getSquareArea();
    std::cout << "Square of square (lol): " << area << std::endl;
    return 0;
}