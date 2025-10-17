#include <iostream>

std::string OctalForm(int number) {
	std::string octal_form = "";
	std::string octal_symbols = "01234567";
	int number_copy = number;

	while (number_copy > 0) {
		octal_form = octal_symbols[number_copy % 8] + octal_form;
		number_copy /= 8;
	}
	return octal_form;
}
std::string HexalForm(int number) {
	std::string hexal_form = "";
	std::string hex_symbols = "0123456789ABCDEF";
	int number_copy = number;

	while (number_copy > 0) {
		hexal_form = hex_symbols[number_copy % 16] + hexal_form;
		number_copy /= 16;
	}
	return hexal_form;
}

int main() {
	int number;
	std::cout << "Enter the number for converting: ";
	std::cin >> number;
	if (number == 0) {
		std::cout << "Octal form: " << "0" << "\n";
		std::cout << "Hexademical form: " << "0";
	}
	else {
		std::cout << "Octal form: " << OctalForm(number) << "\n";
		std::cout << "Hexademical form: " << HexalForm(number);
	}
}