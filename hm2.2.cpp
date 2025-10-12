#include <iostream>

int main()
{
    setlocale(LC_ALL, "RU");
    int num;
    std::cout << "Введите число: ";
    std::cin >> num;
    std::cout << "-------------------------------------------------------------"<<std::endl;
    while (num > 1) {
        if (num % 2 == 1) {
            num = num * 3;
            num = num + 1;
            num = num / 2;
        }
        if (num % 2 == 0) {
            num = num / 2;
        }
    }
    std::cout << num;
    return 0;
}


