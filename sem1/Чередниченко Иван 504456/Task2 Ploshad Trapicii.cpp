#include <iostream>
using namespace std;

int S(int a, int b, int h) 
{
    cout << ((a + b) * h) / 2;
    return 0;
}

int main()
{
    setlocale(LC_ALL,"rus");
    int a, b, h;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "h = ";
    cin >> h;

    cout << "S = ";

    S(a, b, h);
}

