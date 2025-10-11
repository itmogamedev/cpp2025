//площадь квадрата//
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	float storona;
	cout << "Введите сторону квадрата = ";
	cin >> storona;
	cout << "Площадь вашего квадрата равна = " << storona * storona << endl;
}
//площадь трапеции//
#include <iostream>

using namespace std;

int main()
{
	float h, a, b;
	setlocale(LC_ALL, "RUS");
	cout << "Введите высоту = ";
	cin >> h;
	cout << "Введите первую сторону = ";
	cin >> a;
	cout << "Введите вторую сторону = ";
	cin >> b;
	cout << "Площадь трапеции равна = " << (0.5 * (a + b)) * h << endl;
}
