#include <iostream>
#include <algorithm>
#include <string>

int main()
{
    setlocale(LC_ALL, "Rus");

    int variant;
    std::string New_chislo{};
    std::string New_chislo2{};
    const char alf[17] = { "0123456789ABCDEF" };
    
    std::cout << "Выберите систему счисления: " << std::endl;
    std::cout << "1. 8" << std::endl;
    std::cout << "2. 16" << std::endl;
    std::cin >> variant;

    switch (variant)
    {
        case 1:
            int chislo1;
            std::cout << "Вы выбрали восьмеричную систему счисления" << std::endl;
            std::cout << "Введите число: " << std::endl;
            std::cin >> chislo1;

            while (chislo1 > 0)
            {
                New_chislo = {std::to_string(chislo1 % 8) + New_chislo};
                chislo1 /= 8;
            }

            std::cout << New_chislo;
            break;
    
        case 2:
            int chislo2, per;
            std::cout << "Вы выбрали шестнадцатеричную систему счисления" << std::endl;
            std::cout << "Введите число: " << std::endl;
            std::cin >> chislo2;
            
            while (chislo2 > 0)
            {
                per = chislo2 % 16;
                chislo2 /= 16;
                New_chislo2 = { alf[per] + New_chislo2};
                
            }

            std::cout << New_chislo2;
            break;
        
        default:std::cout << "нет такого варианта";
            break;
    } 
}


