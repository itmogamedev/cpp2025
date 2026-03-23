#include <iostream>

#include "Vec3Lib.h"

void test() {
    Vec3 vector1(1, 2, 3);
    Vec3 vector2(2, 5, 4);
    Vec3 vector3(vector2);

    std::cout << "Векторы: " << vector1 << " " << vector2 << " " << vector3
        << std::endl;
    std::cout << "Векторное произведение vector1 и vector3: "
        << vector1.cross(vector3) << std::endl;
    std::cout << "Скалярное произведение vector1 и vector2: "
        << vector1.dot(vector2) << std::endl;
    std::cout << "Длина vector1: " << vector1.length() << std::endl;

    vector2.normalize();
    std::cout << "Нормализованный vector2: " << vector2 << std::endl;
    std::cout << "Нормализованный vector3: " << vector3.normalized() << std::endl;

    std::cout << "Сложение и вычитание векторов: " << (vector1 + vector2) << " "
        << (vector2 - vector3) << std::endl;
    std::cout << "Умножение вектора на скаляр: " << (vector1 * 2.4f) << std::endl;
}

int main() {
    test();
    return 0;
}