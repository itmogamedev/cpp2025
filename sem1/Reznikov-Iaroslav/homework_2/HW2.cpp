#include <iostream>
#include <string>
#include <cassert>

std::string from10toN(std::string, int);
std::string from10toN(int, int);
void theSyracuseHypothesis(int num);

int main(){
    int numForHypothesis;
    std::cout << "Enter number to check the Syracuse hypothesis: ";
    std::cin >> numForHypothesis;
    theSyracuseHypothesis(numForHypothesis);

    // for(int i = 0; i < 50; i++){
    //     std::cout << "10b: " << i << ", 8b: "<< From10toN(i, 8) << ", 16b: "<< From10toN(i, 16) <<std::endl;
    // }
    return 0;
}

void theSyracuseHypothesis(int num){
    std::cout << num << "->";
    while(num > 1){
        if(num % 2 == 0){
            num = num / 2;
        }
        else{
            num = ((num * 3) + 1) / 2;            
        }
        if(num == 1){
            std::cout << num << std::endl;
        }
        else{
            std::cout << num << "->";
        }
    }

}

std::string from10toN(std::string snum10, int N){
    assert(N <= 16);
    std::string symbols[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    int inum10 = std::stoi(snum10);
    std::string snumN = "";
    do{
        snumN = symbols[(inum10%N)] + snumN;
        inum10 = inum10 / N;
    }
    while(inum10 > 0);

    return snumN;
}


std::string from10toN(int inum10, int N){
    return from10toN(std::to_string(inum10), N);
}

int convertStringToInt(std::string str){
    return std::stoi(str);
}