#include <iostream>

void convertHexAndOct(int num) {
    std::cout << "Hexadecimal: " << std::hex << num << std::endl;
    std::cout << "Octal: " << std::oct << num << std::endl;
}

int main() {
    int num;
    std::cout << "Enter decimal number: ";
    std::cin >> num;

    convertHexAndOct(num);
    
    return 0;
}