#include <iostream>
#include <locale>

double calculateTrapezoidArea(double base_a, double base_b, double height) {
    return ((base_a + base_b) / 2.0) * height;
}

int main() {
    setlocale(LC_ALL, "");  

    double base_a;
    double base_b;
    double height;

    std::cout << "Введите основание A трапеции: ";
    std::cin >> base_a;

    std::cout << "Введите основание B трапеции: ";
    std::cin >> base_b;

    std::cout << "Введите высоту трапеции: ";
    std::cin >> height;

    std::cout << "Площадь трапеции = "
        << calculateTrapezoidArea(base_a, base_b, height) << std::endl;

    return 0;
}
