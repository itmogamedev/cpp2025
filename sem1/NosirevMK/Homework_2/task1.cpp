#include <iostream>

int main() {
  int number;
  std::cout << "Enter number: ";
  std::cin >> number;
  std::cout << "octal: ";
  int temp = number;
  if (temp == 0) {
      std::cout << "0" << std::endl;
  }
  if (temp < 0) {
      std::cout << "-" << std::endl;
      temp = -temp;
  }
  int octal = 0, place = 1;
  while (temp > 0) {
      octal = octal + (temp % 8) * place;
      temp = temp / 8;
      place = place * 10;
  }
  std::cout << octal << std::endl;
  std::cout << "hexadecimal: ";
  temp = number;
  if (temp == 0) {
      std::cout << "0";
  }

  if (temp < 0) {
      std::cout << "-";
      temp = -temp;
  }
  char hex[100];
  int i = 0;
  while (temp > 0) {
      int remainder = temp % 16;
      if (remainder < 10) {
            hex[i] = '0' + remainder;
      }
      else {
          hex[i] = 'A' + (remainder - 10);
      }
      temp = temp / 16;
      i++;
  }
  for (int j = i - 1; j >= 0; j--) {
      std::cout << hex[j];
  }

  return 0;
}
