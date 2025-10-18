#include <iostream>
#include <string>

std::string Dec2Oct(int Number)
{
    std::string OctResult;
    for (; Number; Number /= 8)
        OctResult = char('0' + Number % 8) + OctResult;

	return OctResult.empty() ? "0" : OctResult;
}

std::string Dec2Hex(int Number)
{
    std::string HexChars = "0123456789ABCDEF";
    std::string HexResult;

    while (Number > 0) {
        HexResult = HexChars[Number % 16] + HexResult;
        Number /= 16;
    }

    return HexResult.empty() ? "0" : HexResult;
}

int main() {
    int Number;

    std::cout << "Enter a number to convert it from Dec to Oct: ";
	std::cin >> Number;
    std::cout << Number << " -> " << Dec2Oct(Number) << std::endl;
	std::cout << "Enter a number to convert it from Dec to Hex: ";
    std::cin >> Number;
    std::cout << Number << " -> " << Dec2Hex(Number) << std::endl;;

	return 0;
}