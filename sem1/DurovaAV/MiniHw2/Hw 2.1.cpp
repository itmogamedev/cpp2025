#include <iostream>
#include <sstream>

int main()
{
    int num;
    std::cout << "Enter a number ";
    std::cin >> num;
    std::cout << "Here is shestnadtsatirichnaya: " << std::hex << num << '\n';
    std::cout << "Here is vosmirichnaya: " << std::oct << num << '\n';
    return 0;
}