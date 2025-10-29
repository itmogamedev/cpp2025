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

#include<iostream>
using namespace std;
void main()
{
	setlocale(LC_ALL, "ru");
	float a, b, h;
	float s;
	cout << "Введите числа" << endl;
	cin >> a >> b >> h;
	s = ((a + b)/2) * h;
	cout << "Площадь равна=" << s << endl;
}

//#include<iostream>
//using namespace std;
//void main()
//{
//	const int pass = 123;
//	int input = 0;
//	cin >> input;
//	cout << "Pass is" +
//		(pass == input
//			? "OK"
//			: "wrong");
//
//}

//#include<iostream> 
//int main(){
//	const int field_x = 10;
//	const int field_y = 10;
//	const int field_z = 10;
//	int field[field_x][field_y][field_z];
//
//	int field_num = 0;
//	for (int x = 0; x < field_x; x++) {
//		for (int x = 0; x < field_x; x++) {
//			field[x][y] = field_num++;
//		}

	}


//#include<iostream>
//
//	struct Salary {
//		int clean;
//		int tax;
//		std::string name;
//	}
//
//	int main() {
//		Salary mySal;
//		mySal.clean = 20000;
//		mySal.name = "pre";
//
//		Salary mySalstudent;
//		mySalstudent.name = "Vasyapupkin";
//		mySalstudent.clean = 1;
//		std::cout << mySal.name << mySal.clean;
//	}



#include<iostream>
	int main() {
		int arr[5];
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		arr[3] = 4;
		arr[4] = 5;
		std::cout << arr[0] << arr[1] << arr[2] << arr[3] << arr[4];
	}






//класс новый тип данных который соединяет в себе код и данные пример class DateClass{}


