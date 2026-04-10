#include <iostream>
#include "Vec3Lib.h"
#include <Windows.h>

#define NOMINMAX

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Vec3 v1(1, 2, 3);
    Vec3 v2(4, 5, 6);

    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;

    Vec3 sum = v1 + v2;
    std::cout << "v1 + v2 = " << sum << std::endl;

    Vec3 razn = subtract(v1, v2);
    std::cout << "v1 - v2 = " << razn << std::endl;

    Vec3 multiplied = v1 * 2.5;
    std::cout << "v1 * 2.5 = " << multiplied << std::endl;
    multiplied = 3.0 * v2;
    std::cout << "3.0 * v2 = " << multiplied << std::endl;

    double scalared = scalMult(v1, v2);
    std::cout << "(v1, v2) = " << scalared << std::endl;

    Vec3 vectored = vectMult(v1, v2);
    std::cout << "[v1 x v2] = " << vectored << std::endl;

    std::cout << "Модуль v1 = " << length(v1) << std::endl;

    Vec3 norm = normalize(v1);
    std::cout << "Нормализованный v1 = " << norm << std::endl;
    std::cout << "Модуль нормализованного v1 = " << length(norm) << std::endl;

}