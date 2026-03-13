#include <iostream>
#include "Vec3.h"

int main() {


    Vec3 a(1.0, 2.0, 3.0);
    Vec3 b(4.0, 5.0, 6.0);

    std::cout << "vector a = " << a << std::endl;
    std::cout << "vector b = " << b << std::endl;

    // Сложение
    Vec3 sum = a + b;
    std::cout << "a + b = " << sum << std::endl;

    // Вычитание
    Vec3 diff = a - b;
    std::cout << "a - b = " << diff << std::endl;

    // Умножение на скаляр
    Vec3 scaled = a * 2.5;
    std::cout << "a * 2.5 = " << scaled << std::endl;
    Vec3 scaled2 = 0.5 * a;
    std::cout << "0.5 * a = " << scaled2 << std::endl;

    // Скалярное произведение
    double dotProduct = dot(a, b);
    std::cout << "dot(a, b) = " << dotProduct << std::endl;

    // Векторное произведение
    Vec3 crossRes = cross(a, b);
    std::cout << "cross(a, b) = " << crossRes << std::endl;

    // Длина вектора
    double lenA = length(a);
    std::cout << "length(a) = " << lenA << std::endl;

    // Нормализация
    Vec3 normA = normalize(a);
    std::cout << "normalize(a) = " << normA << std::endl;
    std::cout << "normalized vectors length: " << length(normA) << std::endl;

    return 0;
}