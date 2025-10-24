#include <iostream>
#include <string>

std::string to_hex(int n) {
    if (n == 0) return "0";

    std::string alphabet = "0123456789ABCDEF";
    std::string result = "";
    int num = n;

    while (num > 0) {
        int ostatok = num % 16;
        result = alphabet[ostatok] + result;
        num = num / 16;
    }

    return result;
}
std::string to_octal(int n) {
    if (n == 0) return "0";

    std::string result = "";
    int num = n;

    while (num > 0) {
        int ostatok = num % 8;
        result = std::to_string(ostatok) + result;
        num = num / 8;
    }

    return result;
}
int main() {
    int number;

    std::cout << "Write desitichnoe number: ";
    std::cin >> number;

    std::cout << "\nResults:" << std::endl;
    std::cout << "desitichnoe: " << number << std::endl;
    std::cout << "Sixteenarichnot: " << to_hex(number) << std::endl;
    std::cout << "Vosmirichnoe: " << to_octal(number) << std::endl;
    return 0;
}