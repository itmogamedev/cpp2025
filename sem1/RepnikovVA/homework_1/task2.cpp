#include <iostream>
#include <string>

float trapeze(float a, float b, float h) {
	return 0.5 * (a + b) * h;
}

float* separate(char input[100]) {
	std::string el;
	float data[3];
	int i = 0, c = 0;
	while (c != 3) {
		if (input[i] != ' ') {
			el += input[i];
		}
		else {
			data[c] = stof(el);
			c++;
			el.clear();
		}
		i++;
	}
	return data;
}

int main() {

	setlocale(LC_ALL, "Russian");

	char input[100];
	std::cout << "Введите длины оснований трапеции и высоту соответственно (через пробел): ";
	std::cin.getline(input, 100);

	float* s;
	s = separate(input);
	float res2;
	res2 = trapeze(s[0], s[1], s[2]);

	std::cout << res2;

	return 0;
}