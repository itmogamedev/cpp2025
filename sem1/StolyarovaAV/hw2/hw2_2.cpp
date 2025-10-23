#include <iostream>
int main()
{
    int num;
    std::cout << "Введите число:";
    std::cin >> num;
    while (num != 1)
    {
        if (num % 2 == 0)
        {
            num /= 2;
        }
        else
        {
            num = (num * 3 + 1)/2;
        }
        std::cout << num << ' ';
    }
}