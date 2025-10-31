
#include <iostream>
using namespace std;
#include <string>
#include<algorithm>
string decemalToHex(int n) {
	int x;
	string result = "";
	string a = "01234567";
	while (n > 0) {
		x = n % 8;
		result += a[x];
		n = n / 8;


	}std::reverse(result.begin(), result.end());
	return result;

}
int main()
{
	string result = "";
	int n;
	cin >> n;
	cout << decemalToHex(n);



}
