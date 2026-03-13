#include <iostream>
// Подключаем заголовок библиотеки. 
// Путь зависит от того, где лежит проект VecLib относительно ClientApp
#include "..\..\VecLib\VecLib\VecLib.h" 

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    std::cout << "=== Тестирование VecLib.dll ===" << std::endl;

    // 1. Создание векторов
    Vec3 v1(1.0f, 2.0f, 3.0f);
    Vec3 v2(4.0f, 5.0f, 6.0f);

    std::cout << "Вектор 1: " << v1 << std::endl;
    std::cout << "Вектор 2: " << v2 << std::endl;

    // 2. Сложение и вычитание (операторы +, -)
    Vec3 vSum = v1 + v2;
    Vec3 vDiff = v1 - v2;
    std::cout << "Сложение (v1 + v2): " << vSum << std::endl;
    std::cout << "Вычитание (v1 - v2): " << vDiff << std::endl;

    // 3. Умножение на скаляр (оператор *)
    float scalar = 2.0f;
    Vec3 vScaled = v1 * scalar;
    Vec3 vScaled2 = scalar * v1; // Проверка дружественной функции
    std::cout << "Умножение на скаляр (v1 * 2): " << vScaled << std::endl;
    std::cout << "Умножение на скаляр (2 * v1): " << vScaled2 << std::endl;

    // 4. Скалярное произведение
    float dot = DotProduct(v1, v2);
    std::cout << "Скалярное произведение: " << dot << std::endl;

    // 5. Векторное произведение
    Vec3 vCross = CrossProduct(v1, v2);
    std::cout << "Векторное произведение: " << vCross << std::endl;

    // 6. Длина и нормализация
    float len = v1.Length();
    Vec3 vNorm = v1.Normalize();
    std::cout << "Длина вектора v1: " << len << std::endl;
    std::cout << "Нормализованный v1: " << vNorm << std::endl;
    std::cout << "Длина нормализованного: " << vNorm.Length() << std::endl;

    std::cout << "\nНажмите Enter для выхода...";
    std::cin.get();

    return 0;
}