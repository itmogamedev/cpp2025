#include <iostream>

int main()
{
    int number;
    std::cin >> number;
    while (number != 1){
        if (number % 2 == 0)
        {
            number = number / 2;
        }
        else
        {
            number = (number * 3 + 1) / 2;
        }
    }
    if (number == 1)
    {
        std::cout << "Теория верна" << std::endl;
    }
    return 0;
}