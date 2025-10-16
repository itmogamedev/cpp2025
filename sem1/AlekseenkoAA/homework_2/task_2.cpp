// task_2.cpp : проверяет гипотезу Сиракуз
 #include <iostream>
#include <string>
#include <limits>

int main() {
    // std::setlocale(LC_CTYPE, "Russian"); // На двух разных компах почему c++ работает по разному: один не выводит русский язык с setlocal(), а другой выводит русский только без setlocale()
    /* Программа Сиракуз */
    std::cout << "Программа, которая проверяет гипотезу Сиракуз \n";
    unsigned long long sample_b;
    unsigned long long operations_count = 0;
    std::cout << "Введите любое натуральное число: ";
    std::cin >> sample_b;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true) {
        if (sample_b == 1ULL) {
            break;
        }
        else if (sample_b % 2 == 0ULL) {
            sample_b /= 2ULL;
        }
        else {
            sample_b *= 3ULL;
            sample_b += 1ULL;
            sample_b /= 2ULL;
        }
        operations_count += 1ULL;
    }
    std::cout << "Полученное число после преобрезований: " << sample_b << "\n" << "Затраченно операций цикла: " << operations_count << "\n";
    if (sample_b == 1ULL) {
        std::cout << "Теория Сиракуза верна";
    }
    else {
        std::cout << "Теория Сиракуза НЕ верна";
    }
    return 0;
}