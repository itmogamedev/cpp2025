#include "Vec3Lib.h"
#include <iostream>
#include <locale>
int main()
{
    setlocale(LC_ALL, "");
    Vec3 v_1(1, 7, 8);
    Vec3 v_2(2, 5, 6);
    std::cout << "Демонстрация библиотеки" << std::endl;
    std::cout << "Вектор 1: " << v_1<< std::endl;
    std::cout << "Вектор 2: " <<v_2 << std::endl;
    std::cout << "Сумма: " <<v_1+v_2 << std::endl;
    std::cout << "Разность: " <<v_1 - v_2 << std::endl;
    std::cout << "Умножение на скаляр вектора 1: " <<v_1*7 << std::endl;
    std::cout << "Скалярное произведение: " << v_1*v_2 << std::endl;
    std::cout << "Векторное произведение: " <<crossProduct(v_1,v_2) << std::endl;
    std::cout << "Длинна вектора 1: " <<v_1.length() << std::endl;
    std::cout << "Нормализация вектора 1: " <<v_1.normalize()<< std::endl;
}

