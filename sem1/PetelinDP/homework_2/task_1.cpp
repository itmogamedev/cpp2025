#include <iostream>
#include <string>

std::string toOctal(int number) {
    if (number == 0) return "0";

    std::string result;

    while (number > 0) {
        result = std::to_string(number % 8) + result;
        number /= 8;
    }

    return result;
}

std::string toHexadecimal(int number) {
    if (number == 0) return "0";

    const std::string hexDigits = "0123456789ABCDEF";
    std::string result;

    while (number > 0) {
        result = hexDigits[number % 16] + result;
        number /= 16;
    }

    return result;
}

int main() {
    int decimalNum;
    std::cout << "Enter a decimal number: ";
    std::cin >> decimalNum;

    std::string octal = toOctal(decimalNum);
    std::string hexadecimal = toHexadecimal(decimalNum);

    std::cout << "In the octal system: " << octal << std::endl;
    std::cout << "In hexadecimal: " << hexadecimal << std::endl;
}