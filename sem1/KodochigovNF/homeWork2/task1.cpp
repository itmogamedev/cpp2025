#include <iostream>
#include <string>
#include <locale>

std::string decimalToOctal(int number) {
    std::string result;

    if (number == 0) return "0";

    while (number > 0) {
        int remainder = number % 8;
        result = static_cast<char>('0' + remainder) + result;
        number /= 8;
    }

    return result;
}

std::string decimalToHex(int number) {
    constexpr char kHexDigits[] = "0123456789ABCDEF";
    std::string result;

    if (number == 0) return "0";

    while (number > 0) {
        int remainder = number % 16;
        result = kHexDigits[remainder] + result;
        number /= 16;
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "");  

    int user_number;
    std::cout << "Введите десятичное число: ";
    std::cin >> user_number;

    std::string octal_result = decimalToOctal(user_number);
    std::string hex_result = decimalToHex(user_number);

    std::cout << "Восьмеричная система: " << octal_result << std::endl;
    std::cout << "Шестнадцатеричная система: " << hex_result << std::endl;

    return 0;
}
