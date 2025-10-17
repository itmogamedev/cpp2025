#include <iostream>

int main() {
    int startNumber;

    std::cout << "Enter any natural number: ";
    std::cin >> startNumber;

    if (startNumber <= 0) {
        std::cout << "You can only enter a natural number!" << std::endl;
    }
    else {
        while (startNumber != 1) {
            if (startNumber % 2 == 0) {
                startNumber /= 2;
            }
            else {
                startNumber = (startNumber * 3 + 1) / 2;
            }
        }

        std::cout << startNumber << std::endl;
    }
}