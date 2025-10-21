#include <iostream>
#include <string>
#include <locale.h>

int CyrakusCheck(int val) {
    while (val > 1) {
        if (val % 2 == 0) val /= 2;
        else val = (val * 3 + 1) / 2;
    }
    return val;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int val = 0;
    std::cout << "¬ведите число: ";
    std::cin >> val;
    std::cout << CyrakusCheck(val);
}