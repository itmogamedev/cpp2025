#include <iostream>

int S_tr(int a, int b, int h){
    int s;
    s = ((a+b)/2)*h;
    return s;
}
int main(){
    int num_A, num_B, num_h;
    std::cout << "Enter a side values trapezoid A == ";
    std::cin >> num_A;
    std::cout << "Enter a side values trapezoid B == ";
    std::cin >> num_B;
    std::cout << "Enter a height values trapezoid h == ";
    std::cin >> num_h;
    int result_tr = S_tr(num_A, num_B, num_h); 
    std::cout << " The area trapezoid = " << result_tr << '\n';
    return 0;
}
