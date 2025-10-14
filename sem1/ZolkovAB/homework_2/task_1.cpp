#include <iostream>

int main(){
    int num;

    std::cout << "Enter a number: ";
    std::cin >> num;
    if (num = 1){
        std::cout << "write another number!!! ";
        std::cin >> num;
    }
    
    while (num != 1){
        if (num % 2 == 0){
            num = num / 2;
        }
        else{
            num = (num * 3 + 1) / 2;
        }
    }
    std::cout << "The hypothesis is true";

}