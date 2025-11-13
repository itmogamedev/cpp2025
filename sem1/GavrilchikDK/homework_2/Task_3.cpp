#include <iostream>
#include <string>
using namespace std;
string To_base(int num, int base)
{
    string digits = "0123456789ABCDEF";
    string result = "";
    if (num == 0) return "0";
    
    while (num > 0)
    {
        int ost = num % base;
        result = digits[ost] + result;
        num /= base;
        
    }
    return result;
}
int main() {
    int number; 
    cout << "Your number" ;
    cin >> number;
    cout << "Oct base :" << To_base(number,8)<< endl;
    cout << "Hex base :" << To_base(number,16)<< endl;
    return 0;
}


