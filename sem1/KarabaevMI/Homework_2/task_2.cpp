#include<iostream>
void sirakus(int n){
    std::cout<<n<<" ";
    while (n>1)
    {
        if (n%2 == 0) 
        {
            n = n / 2;
            std::cout<<n<<" ";
        }
        else {
            n = (n*3 + 1)/2;
            std::cout<<n<<" ";
        }
    }
    
}
int main(){
    sirakus(71);
    return 0;
}