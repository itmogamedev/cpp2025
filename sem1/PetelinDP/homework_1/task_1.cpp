#include <iostream>

int main() {
    float side_length;
    float s;

    std::cout << "Type side length" << std::endl;
    std::cin >> side_length;

    s = pow(side_length, 2);

    std::cout << "S = " << s << std::endl;
}