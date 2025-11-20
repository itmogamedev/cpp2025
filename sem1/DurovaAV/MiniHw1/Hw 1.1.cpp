#include <iostream>

int main() {
    int side;
    std::cout << "The side of the square? ";
    std::cin >> side;
    std::cout << "The area of the square is " << side * side;
    return 0;
}