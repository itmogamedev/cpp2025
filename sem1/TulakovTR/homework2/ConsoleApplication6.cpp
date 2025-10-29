

#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    int a;
    cin >> a;
    while (a != 1) {
        cout << a << "-";
        if (a % 2 == 0) {
            a = a / 2;
        }
        else {
            a = ((a * 3) + 1) / 2;
        }

    }
    cout << "1" << endl;

}
