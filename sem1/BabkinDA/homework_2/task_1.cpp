#include <iostream>
#include <cstdio>

void printAllBases(int number) {
    printf("Шестнадцатеричное: %X\n", number);
    printf("Восьмеричное: %o\n", number);
}

int main() {
    int number;
    std::cout << "Введите десятичное число: ";
    std::cin >> number;
    printAllBases(number);
}