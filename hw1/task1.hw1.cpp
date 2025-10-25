#include<iostream>
float S_sq(int a)
{
    return a*a;
}

int main(){
    int input;
    std::cout << "tipe side lenght ";
    std::cin >> input;

    std::cout << std::endl << "S = " << S_sq(input) << "\n";
}