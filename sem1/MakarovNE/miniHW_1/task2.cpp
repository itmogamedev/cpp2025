#include <iostream>
#include <cmath>

int main() {
    int variant = 0;
    int side_a = 0;
    int side_b = 0;
    int height = 0;
    int d1 = 0;
    int d2 = 0;
    int angle_deg = 0;
    double result = 0.0;

    while (true) {
        std::cout << "Calculation of the trapezoid area" << std::endl;
        std::cout << "Variants:" << std::endl;
        std::cout << "1) By the lengths of the bases and height\n"
            << "2) By two diagonals and the angle between them\n";
        std::cout << "Choose variant (1 or 2): ";
        std::cin >> variant;

        if (variant == 1) {
            std::cout << "Enter first base: ";
            std::cin >> side_a;
            std::cout << "Enter second base: ";
            std::cin >> side_b;
            std::cout << "Enter height: ";
            std::cin >> height;

            result = ((side_a + side_b) * height) / 2.0;
            std::cout << "Trapezoid area: " << result << std::endl;

        }
        else if (variant == 2) {
            std::cout << "Enter first diagonal: ";
            std::cin >> d1;
            std::cout << "Enter second diagonal: ";
            std::cin >> d2;
            std::cout << "Enter angle (in degrees): ";
            std::cin >> angle_deg;

            // Конвертация градусов в радианы
            double angle_rad = angle_deg * M_PI / 180.0;
            result = (d1 * d2 * std::sin(angle_rad)) / 2.0;
            std::cout << "Trapezoid area: " << result << std::endl;

        }
        else {
            std::cout << "Incorrect variant!" << std::endl;
        }

        std::cout << "-----------------------------------" << std::endl;
    }
}
