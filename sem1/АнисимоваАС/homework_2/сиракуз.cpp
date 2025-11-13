#include <iostream>
using namespace std;

int main() {
    int number;
    cout << "Введите начальное число: ";
    cin >> number;

    int steps = 0;
    while (number != 1) {
        if (number % 2 == 0) {
            number = number / 2;
        } else {
            number = (3 * number + 1) / 2;
        }
        steps++;
        cout << number << " ";
    }

    cout << endl << "Достигнуто 1 за " << steps << " шагов." << endl;
    return 0;
}
