#include <iostream>

void chechHypothesis(int a) {
    while (a != 1) {
        if (a % 2 == 0) {
            a /= 2;
        }
        else {
            a = (a * 3 + 1) / 2;
        }
        std::cout << a << std::endl;
    }
    std::cout << "hypothesis is right!";
}
int main()
{
    int a;
    std::cin >> a;
    chechHypothesis(a);
    return 0;
}
