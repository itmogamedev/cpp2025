#include <iostream>
using namespace std;

int main() 
{
    long long n;
    cout << "Введите натуральное число: ";
    cin >> n;

    if (n <= 0) 
    {
        cout << "натуральное! сказано же было: " << endl;
        return 0;
    }

    cout << "Последовательность: " << n << " ";

    while (n != 1) 
    {
        if (n % 2 == 0) 
        {
            n = n / 2;
        }
        else 
        {
            n = (3 * n + 1) / 2;
        }
        cout << n << " ";
    }

    cout << endl << "Гипотеза подтверждена — достигнута 1." << endl;
    return 0;
}
