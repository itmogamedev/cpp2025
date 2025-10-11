//площадь квадрата//
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	int storona;
	cout << "¬ведите сторону квадрата = ";
	cin >> storona;
	cout << "ѕлощадь вашего квадрата равна = " << storona * storona << endl;
}

//площадь трапеции//
#include <iostream>

using namespace std;

int main()
{
	int h, a, b;
	setlocale(LC_ALL, "RUS");
	cout << "¬ведите высоту = ";
	cin >> h;
	cout << "¬ведите первую сторону = ";
	cin >> a;
	cout << "¬ведите вторую сторону = ";
	cin >> b;
	cout << "ѕлощадь трапеции равна = " << (0.5 * (a + b)) * h << endl;
}
