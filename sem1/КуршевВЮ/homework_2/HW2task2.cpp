#include <iostream>

int main()
{
    int n;
    std::cout << "Enter a natural number: ";
    std::cin >> n;
    
    if (n < 1)
    {
        std::cout << "chel ti....";
        return 0;
    }
    
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
    std::cout << "It's 1.";
}