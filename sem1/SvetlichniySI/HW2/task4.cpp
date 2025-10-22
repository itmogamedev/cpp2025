#include <iostream>

int main() {
    std::cout << "vvedite chislo" << std::endl;
    int a;
    std::cin >> a;
    while (true) {
        if (a < 0) {
            std::cout << "vi ne pravi, vsego dobrogo" << std::endl;
            return 1;
        }
        if (a == 1) {
            std::cout << "chislo ravno 1" << std::endl;
            break;
        }
        if (a % 2 == 0) {
            std::cout << "chislo chetnoe: " << a << "/2 == " << a / 2 << std::endl;
            a = a / 2;
        } else {
            std::cout << "chislo nechetnoe: " << a << "*3+1 == " << a * 3 + 1 << std::endl;
            a = 3 * a + 1;
        }
    }
    return 0;
}
