#include <iostream>

int S_sq(int s){
    s = s*s;
    return s;
}

int main(){
    int num_sq;
    std::cout << "Enter a side value square: ";
    std::cin >> num_sq;
    int result_sq = S_sq(num_sq);
    std::cout << " The area square = " << result_sq << '\n';
    return 0;
}
