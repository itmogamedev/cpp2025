#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "ru");
	float a;
	float s;
	cout << "введи число:" << endl;
	cin >> a;
	s = a * a;
	cout << "Площадь равна=" << s << endl;
}