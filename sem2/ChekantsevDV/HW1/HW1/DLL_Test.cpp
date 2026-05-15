#include <iostream>
#include "Dll1.h"

int main() {
    setlocale(LC_ALL, "Russian");

    Vec3 v1(1.0, 2.0, 3.0);
    Vec3 v2(4.0, 5.0, 6.0);

    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;

    Vec3 sum = v1 + v2;
    std::cout << "Сложение векторов v1 + v2 = " << sum << std::endl;

    Vec3 diff = v1 - v2;
    std::cout << "Вычитание векторов v1 - v2 = " << diff << std::endl;

    Vec3 scaled = v1 * 2.5;
    std::cout << "Умножение вектора на скаляр v1 * 2.5 = " << scaled << std::endl;

    double multiplyScalarProduct = multiplyScalar(v1, v2);
    std::cout << "Скалярное произведение (v1, v2) = " << multiplyScalarProduct << std::endl;

    Vec3 multiplyVectorProduct = multiplyVector(v1, v2);
    std::cout << "Векторное произведение (v1, v2) = " << multiplyVectorProduct << std::endl;

    double len = length(v1);
    std::cout << "Длина вектора |v1| = " << len << std::endl;

    Vec3 norma = normalize(v1);
    std::cout << "Нормализация (v1) = " << norma << std::endl;
    std::cout << "|Нормализация (v1)| = " << length(norma) << std::endl;

    return 0;
}