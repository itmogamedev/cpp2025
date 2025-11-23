#include <iostream>
#include <string>
#include <locale.h>

std::string another(int ten, int toAnother)
{
    std::string alph = "0123456789ABCDEF";
    std::string newValu = "";
    
    while (ten > 0) {
        int ost = ten % toAnother;
        newValu = alph[ost] + newValu;
        ten /= toAnother;
    }

    return newValu;
}
int cyrakus(int val) {
    while (val > 1) {
        if (val % 2 == 0) val /= 2;
        else val = (val * 3 + 1) / 2;
    }
    return val;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int ten = 0;
    int toAnother = 0;
    std::cout << "Введите число: ";
    std::cin >> ten;
    std::cout << "Введите новую систему счисления: ";
    std::cin >> toAnother;
    std::cout << "Ваше число в новой системе счисления: ";
    std::cout << another(ten, toAnother) << std::endl;

    int val = 0;
    std::cout << "Введите число: ";
    std::cin >> val;
    std::cout << cyrakus(val);
}