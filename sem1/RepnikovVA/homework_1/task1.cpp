#include <iostream>
#include <string>

using namespace std;

float square(float a) {
	return a * a;
}

int main() {

	setlocale(LC_ALL, "Russian");

	float a;
	cout << "������� ����� ������� ��������: ";
	cin >> a;

	float res = square(a);
	cout << "������� ��������: " << res << endl;

	return 0;
}