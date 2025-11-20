#include <iostream>

int main()
{
    int num;
    std::cout << "Enter a number ";
    std::cin >> num;
    while (num != 1) {
        if (num % 2 == 0) {
            num = num / 2;
        }
        else {
            num = (num * 3 + 1) / 2;
        }
        if (num == 1) {
            std::cout << "It has become 1, as i said!";
        }
    }
    return 0;
}