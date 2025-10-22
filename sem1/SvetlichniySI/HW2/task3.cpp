#include <algorithm>
#include <iostream>
#include <string>

std::string perevod(int d, int ss) {
    std::string a = "";
    char b;
    int temp;
    while (d > 0) {
        temp = d % ss;
        b = (temp < 10) ? ('0' + temp) : ('A' + temp - 10);
        a += b;
        d = d / ss;
    }
    std::reverse(a.begin(), a.end());
    return a;
}

int main() {
    std::cout << "vvedite chislo i sistemu schislenia" << std::endl;
    int d, ss;
    std::cin >> d >> ss;
    std::cout << perevod(d, ss);
}
