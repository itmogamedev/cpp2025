#include <iostream>
#include <string>
#include <locale.h>

int cyrakus_check(int val) { //проверка на гипотезу
    while (val > 1) {
        if (val % 2 == 0) val /= 2;
        else val = (val * 3 + 1) / 2;
    }
    return val;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int val = 0;
    std::cout << "Введите число: ";
    std::cin >> val;
    std::cout << cyrakus_check(val);
}