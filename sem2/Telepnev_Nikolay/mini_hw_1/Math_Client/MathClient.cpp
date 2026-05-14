#include <iostream>
#include <stdexcept>
#include "Vec3.h"

void demonstrate() {
    const Vec3 kVectorA(1.0, 2.0, 3.0);
    const Vec3 kVectorB(4.0, 5.0, 6.0);
    const double kScalar1 = 2.5;
    const double kScalar2 = 3.0;

    std::cout << "a = " << kVectorA << std::endl;
    std::cout << "b = " << kVectorB << std::endl;
    std::cout << "a + b = " << kVectorA + kVectorB << std::endl;
    std::cout << "a - b = " << kVectorA - kVectorB << std::endl;
    std::cout << "a * " << kScalar1 << " = " << kVectorA * kScalar1 << std::endl;
    std::cout << kScalar2 << " * b = " << kScalar2 * kVectorB << std::endl;
    std::cout << "dot(a, b) = " << dot(kVectorA, kVectorB) << std::endl;
    std::cout << "cross(a, b) = " << cross(kVectorA, kVectorB) << std::endl;
    std::cout << "length(a) = " << kVectorA.length() << std::endl;

    Vec3 norm_a = kVectorA.normalize();
    std::cout << "normalize(a) = " << norm_a << std::endl;
    std::cout << "length(normalized a) = " << norm_a.length() << std::endl;
}

int main() {
    try {
        demonstrate();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}