#include <iostream>
#include <string>

std::string SyracuseHypothesis(int Number) {
	std::string Iterations;
	while (Number > 1)
	{
		if (Number % 2 == 0)
		{
			Number = Number / 2;
		}
		else Number = Number * 3 + 1;
		Iterations = Iterations + std::to_string(Number) + " ";
	}
	return Iterations;
}

int main() {
	int Number;

	std::cout << "Enter a number to convert it from Dec to Oct: ";
	std::cin >> Number;
	std::cout << SyracuseHypothesis(Number) << std::endl;;
	return 0;
}