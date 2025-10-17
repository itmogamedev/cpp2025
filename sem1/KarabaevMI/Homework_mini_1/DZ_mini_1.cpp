#include <iostream>
float SquareZone(float s) {
    return s * s;
}
int main() {
    setlocale(LC_ALL, "RU");
    float s;
    std::cout << "Add a side of square: ";
    std::cin >> s;
    std::cout << "Square area: " << SquareZone(s) << std::endl;
    return 0;
}