#include <iostream>

int main()
{
    int num = 1;
    std::cout << "Write number:";
    std::cin >> num;
    std::cout << num << " -> ";
    while (num > 1)
    {
        if (num % 2 == 0)
        {
            num /= 2;
            if (num != 1) std::cout << num << " -> ";
            else std::cout << num;
        }
        else
        {
            num = (num * 3 + 1) / 2;
            std::cout << num << " -> ";
        }
    }
}