#include <iostream>
#include <cstdint>
uint8_t const kOctalUpperBound = 7; //number & 7 == number % 8
uint8_t const kHexUpperBound = 15; //number & 15 == number % 16
uint8_t const kOctalBitDivision = 3; //number << 3 == number // 8
uint8_t const kHexBitDivision = 4; //number << 4 == number // 16

char getHexChar(uint8_t dex_number) {
    if (0 <= dex_number && dex_number <= 9) { //0 - 9
        return ('0' + dex_number);
    } else { //10 - 15
        return ('A' - 10 + dex_number);
    }
}

std::string getHexNumber(uint64_t dex_number) {
    std::string result = {};
    while (dex_number > 0) {
        result = getHexChar(dex_number & kHexUpperBound) + result; // number % 16
        dex_number = dex_number >> kHexBitDivision; // number // 16
    }

    return result;
}

std::string getOctalNumber(uint64_t dex_number) {
    std::string result = {};
    while (dex_number > 0) {
        result = getHexChar(dex_number & kOctalUpperBound) + result; // number % 8
        dex_number = dex_number >> kOctalBitDivision; // number // 8
    }

    return result;
}

int main() {
    uint64_t dex_number;
    char number_system;
    std::cout << "Enter decimal number\n";
    std::cin >> dex_number;
    std::cout << "Print 'o' for octal number, 'h' for hex number\n";
    std::cin >> number_system;
    switch (number_system) {
        case 'o':
            std::cout << getOctalNumber(dex_number) << std::endl;
            break;
        case 'h':
            std::cout << getHexNumber(dex_number) << std::endl;
            break;
        default:
            std::cerr << "Error: invalid input for number system\n";
    }
}
