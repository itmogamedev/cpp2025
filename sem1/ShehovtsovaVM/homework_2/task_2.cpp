#include <iostream>
using namespace std;

void chechHypothesis(int a) {
    while (a != 1) {
        if (a % 2 == 0) {
            a /= 2;
        }
        else {
            a = (a * 3 + 1) / 2;
        }
        cout << a << endl;
    }
    cout << "hypothesis is right!";
}
int main()
{
    int a;
    cin >> a;
    chechHypothesis(a);
    return 0;
}
