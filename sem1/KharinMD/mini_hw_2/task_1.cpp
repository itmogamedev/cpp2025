#include <iostream>
#include <string>
#include <sstream>


std::string сonvertToHex(int decimal_number) {
    std::ostringstream stream;
    stream << std::hex << std::uppercase << decimal_number;
    return stream.str();
}

std::string сonvertToOct(int decimal_number) {
    std::ostringstream stream; 
    stream << std::oct << decimal_number;
    return stream.str();
}

int main() {
    int number;

    std::cout << "Введите десятичное число: ";
    std::cin>> number;

    std::string hex_value = сonvertToHex(number);
    std::string oct_value = сonvertToOct(number);

    std::cout << "Ваше число в шестнадцатиричном представлении: " << hex_value << std::endl;
    std::cout << "Ваше число в восьмеричной форме: " << oct_value << std::endl;

    return 0;
}

