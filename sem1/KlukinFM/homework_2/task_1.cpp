#include <iostream>

int main()
{
    double number;
    std::cout << "Введите число" << std::endl;
    std::cin >> number;
    std::cout << "Десятичное число" << number << std::endl;
    std::cout << "Шестнадцатеричное число " << std::hex << number << std::endl;
    std::cout << "Восьмеричное число " << std::oct << number << std::endl;

    return 0;
}