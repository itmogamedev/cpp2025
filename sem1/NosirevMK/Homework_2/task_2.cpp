#include <iostream>
int main()
{
	std::cout << "Enter number:";
	int a;
	std::cin >> a;
	while (a != 1) 
	{
		if(a % 2 == 0) 
			a = a / 2;
		else 
			a = ((a * 3) + 1) / 2;
	}
	std::cout << "Number reached 1";
	return 0;
}