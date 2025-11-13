#include <iostream>
#include <string>

std::string toHex(int number) 
{
    std::string str = "";
    while (number >= 16) {
        str = (char)(number % 16 + '0') + str;
        number /= 16;
    }
    str = (char)(number % 16 + '0') + str;
    return str;
}

std::string toOct(int number) 
{
    std::string str = "";
    while (number >= 8) {
        str = (char)(number % 8 + '0') + str;
        number /= 8;
    }
    str = (char)(number % 8 + '0') + str;
    return str;
}

int main(void) 
{
    int n;
    std::cin >> n;
    std::cout << "0x" << toHex(n) << "; 0o" << toOct(n) << std::endl;
}