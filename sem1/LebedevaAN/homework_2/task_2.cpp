#include <iostream>
#include <cstdint>

void checkCollatzConjecture(uint64_t number) {
    while (number > 1) {
        if ((number & 1)) { // number % 2 == 1
            number = (3 * number + 1) >> 1; //(3n + 1) // 2
            std::cout << " -> " << number;
        } else { // number % 2 == 0
            number = number >> 1; //n // 2
            std::cout << " -> " << number;
        }
    }

    std::cout << "\nCollatz conjecture wasn't disproven\n";
}

int main() {
    uint64_t number;
    std::cout << "Enter natural number\n";
    std::cin >> number;
    std::cout << number;
    checkCollatzConjecture(number);
}
