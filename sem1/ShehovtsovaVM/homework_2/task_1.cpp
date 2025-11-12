#include <iostream>

void convertFromDecimalToOctal(int a) {
    int oct[1000];
    int i = 0;
    while (a != 0) {
        oct[i] = a % 8;
        a = a / 8;
        i++;
    }
    std::cout << "number in oct: ";
    for (int j = i - 1; j >= 0; j--) {
        std::cout << oct[j];
    }
    std::cout << std::endl;
}
void convertFromDecimalToHexadecimal(int a) {
    int hex[1000];
    int i = 0;
    while (a != 0) {
        hex[i] = a % 16;
        a = a / 16;
        i++;
    }
    std::cout << "number in hex: ";
    for (int j = i - 1; j >= 0; j--) {
        std::cout << hex[j];
    }
    std::cout << std::endl;
}
int main()
{
    int a;
    std::cin >> a;
    convertFromDecimalToOctal(a);
    convertFromDecimalToHexadecimal(a);
    return 0;
}
