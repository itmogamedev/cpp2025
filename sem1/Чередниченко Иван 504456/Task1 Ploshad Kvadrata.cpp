#include <iostream>
using namespace std;

int S(int a, int b)
{
    cout << "S = " << a * b;
    return 0;
}

int main()
{
    int a, b;
    cout << "a = ";
    cin >> a;
    
    cout << "b = ";
    cin >> b;
    S(a, b);
}

