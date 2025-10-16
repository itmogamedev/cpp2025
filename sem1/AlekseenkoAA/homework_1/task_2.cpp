// task_2.cpp : вычисляет площадь трапеции
#include <iostream>
#include <string>
#include <typeinfo>
#include <locale>
#include <cmath>
#include <limits>

double trapeciaSquare(double a, double b, double h) {
    double area_square = ((a + b) * h) / 2;
    return area_square;
}

int main() {
    // std::setlocale(LC_CTYPE, "Russian"); // На двух разных компах почему c++ работает по разному: один не выводит русский язык с setlocal(), а другой выводит русский только без setlocale()
    double a;
    double b;
    double h;
    std::cout << "Функция подсчёта площади трапеции!\n";
    std::cout << "Введите длину нижней грани трапеции: ";
    std::cin >> a;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищает буфер cin
    std::cout << "\nВведите длину верхней грани трапеции: ";
    std::cin >> b;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищает буфер cin
    std::cout << "\nВведите длину высоты трапеции: ";
    std::cin >> h;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищает буфер cin
    try {
        std::cout << "\nПлощадь трапеции: " << std::to_string(trapeciaSquare(a, b, h)) + "\n"; // to_string переводит переменную double в string тип
    }
    catch (std::exception ex) {
        std::cout << "Что то пошло не так(!\n" << ex.what();
        return -1;
    }
    return 0;
}