#include <iostream>
#include <string>

std::string DecToOct(int dec_num)
{
    std::string result;
    result = "";

    while (dec_num != 0)
    {
        int remainder = dec_num % 8;
        result = std::to_string(remainder) + result;
        dec_num = dec_num / 8;
    }
    // return atoi(result);
    return result;
}
std::string DecToHex(int dec_num)
{
    std::string alf = "0123456789ABCDEF";
    std::string result;
    result = "";

    while (dec_num != 0)
    {
        int remainder = dec_num % 16;
        result = alf[remainder] + result;
        dec_num = dec_num / 16;
    }
    // return atoi(result);
    return result;
}


int main()
{
    int num_to_8;
    int num_to_16;
    std::cout << "Введите число, которое хотите преобразовать в восмиричную систему счисления:";
    std::cin >> num_to_8;
    std::cout << DecToOct(num_to_8)<<std::endl;
    std::cout << "Введите число, которое хотите преобразовать в шестандцатиричную систему счисления:";
    std::cin >> num_to_16;
    std::cout << DecToHex(num_to_16)<<std::endl;
    return 1;
}