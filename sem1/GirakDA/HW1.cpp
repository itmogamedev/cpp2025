//������� ��������//
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	int storona;
	cout << "������� ������� �������� = ";
	cin >> storona;
	cout << "������� ������ �������� ����� = " << storona * storona << endl;
}

//������� ��������//
#include <iostream>

using namespace std;

int main()
{
	int h, a, b;
	setlocale(LC_ALL, "RUS");
	cout << "������� ������ = ";
	cin >> h;
	cout << "������� ������ ������� = ";
	cin >> a;
	cout << "������� ������ ������� = ";
	cin >> b;
	cout << "������� �������� ����� = " << (0.5 * (a + b)) * h << endl;
}
