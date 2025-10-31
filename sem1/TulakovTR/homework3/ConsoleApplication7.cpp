// ConsoleApplication7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
#include <string>
#include<algorithm>
string decemalToHex(int n) {
	int x;
	string result = "";
	string a = "0123456789ABCDEF";
	while (n > 0) {
		x = n % 16;
		result += a[x];
		n = n / 16;


	}std::reverse(result.begin(), result.end());
	return result;

}
int main()
{
	string result= "";
	int n;
	cin >> n;
	cout << decemalToHex(n);

	
 
}
