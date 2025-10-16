#include <iostream>
#include <string>

using namespace std;

float square(float a) {
	return a * a;
}

int main() {

	setlocale(LC_ALL, "Russian");

	float a;
	cout << "¬ведите длину стороны квадрата: ";
	cin >> a;

	float res = square(a);
	cout << "ѕлощадь квадрата: " << res << endl;

	return 0;
}