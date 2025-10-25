#include <iostream>
#include <string>

void toEightAndSixteen(int num)
{
    const char alf[17] = { "0123456789ABCDEF" };
    std::string num8{};
    int temp = num;
    
    while (num > 0)
    {
        num8 = {alf[num % 8] + num8};
        num /= 8;
    }
    std::cout << "8: " << num8 << std::endl;
    
    num = temp;
    std::string num16{};
    
    while (num > 0)
    {
        num16 = {alf[num % 16] + num16};
        num /= 16;
    }

    std::cout << "16: " << num16;
}

int main()
{
    int num;
    std::cout << "Input number: ";
    std::cin >> num;
    toEightAndSixteen(num);
}
