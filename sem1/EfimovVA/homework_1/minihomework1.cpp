//#include <iostream>
//
//double getSquareArea() {
//    double side;
//    std::cout << "Write a side of square: ";
//    std::cin >> side;
//    return side * side;
//}
//
//int main() {
//    double area = getSquareArea();
//    std::cout << "Square of square (lol): " << area << std::endl;
//    return 0;
}
#include <iostream>

double parallelogramArea() {
    double base, height;

    std::cout << "Write a side of paralelogram: ";
    std::cin >> base;
    std::cout << "Write a height of paralelogram: ";
    std::cin >> height;

    return base * height;
}

int main() {
    double area = parallelogramArea();
    std::cout << "Square of paralelograma: " << area << std::endl;
    return 0;
}