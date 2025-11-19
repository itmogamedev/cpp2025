#include <iostream>

std::string toBase(int number, int base)
{
    std::string converted = "";
    std::string symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int n = number;

    while (n > 0)
    {
        converted = symbols[n % base] + converted;
        n /= base;
    }
    return converted;
}

void ConvertNumber()
{
    int number;
    std::cout << "Enter the number for converting: ";
    std::cin >> number;

    std::cout << "Oct: " << toBase(number, 8) << std::endl;
    std::cout << "hex: " << toBase(number, 16) << std::endl;
}

int syracuse(int number)
{
    while (number != 1)
    {
        if (number % 2 == 0)
        {
            number /= 2;
        }
        else
        {
            number = (number * 3 + 1) / 2;
        }
    }

    return 1;
}

void SyracuseHypothesis()
{
    int number;
    std::cout << "Pick a natural number: ";
    std::cin >> number;

    while (number != 1)
    {
        if (number % 2 == 0)
        {
            number /= 2;
            std::cout << number << " ";
        }
        else
        {
            number = (number * 3 + 1) / 2;
            std::cout << number << " ";
        }
    }
    std::cout << std::endl
              << "Syracuse's hypothesis confirmed";
}

int main(void)
{
    int option;
    bool selected = false;

    while (!selected)
    {
        std::cout << "Select task:\n\t- [1] Convent number\n\t- [2] Syracuse hypothesis\n(1-2): ";
        std::cin >> option;
        if (option == 1)
        {
            ConvertNumber();
            selected = true;
        }
        else if (option == 2)
        {
            SyracuseHypothesis();
            selected = true;
        }
        else
        {
            std::cout << "Wrong option\n";
            selected = false;
        }
    }

    return 1;
}