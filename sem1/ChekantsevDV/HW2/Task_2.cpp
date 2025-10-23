#include <iostream>

int main()
{
    int n;
    setlocale(LC_ALL, "Rus");

    std::cout << "Проверка гипотезы Сиракуз" << std::endl;
    std::cout << "Введите любое натуральное число: _";
    std::cin >> n;
    if (n > 0)
    {
        while (n != 1)
        {
            if (n % 2 == 0)
            {
                n /= 2;
                std::cout << n << std::endl;
            }

            else
            {
                n = (n * 3 + 1) / 2;
                std::cout << n << std::endl;
            }
        }
        std::cout << "В конце получилась 1, гипотеза подтвердилась";
        
    }
    else
    {
        std::cout << "Введено не натуральное число";
    }
}