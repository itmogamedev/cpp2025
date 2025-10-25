#include <iostream>

typedef unsigned int u32;

bool foo(u32 n, u32 iter) {
    if(n == 1) return true;
    if(iter == 0) return false;
    n = ((n % 2 == 0) ? n : (n * 3 + 1)) / 2;
    return foo(n, iter - 1);
}

int main(int argc, char** argv) {
    u32 input;
    while(true) {
        std::cout << "enter number, use 0 for exit\n";
        std::cin >> input;
        if(input == 0) {
            std::cout << "exiting the programm!\n";
            return 0;
        }
        if(foo(input, 1000)) {
            std::cout << "all good!\n";
        } else {
            std::cout << "does not apply for this number!\n";
            return 1;
        }
    }
    return 0;
}
