#include <iostream>
#include <string>

std::string oct(int number) {
  if (number == 0) {
    return "0";
  }

  bool is_negative = number < 0;
  unsigned int unsigned_number = std::abs(number);
  std::string result;

  while (unsigned_number > 0) {
    int remainder = unsigned_number % 8;
    result += '0' + remainder;
    unsigned_number /= 8;
  }

  if (is_negative) {
    result += '-';
  }

  std::reverse(result.begin(), result.end());
  return result;
}

std::string hex(int number) {
  if (number == 0) {
    return "0";
  }

  bool is_negative = number < 0;
  unsigned int unsigned_number = std::abs(number);
  std::string result;

  while (unsigned_number > 0) {
    int remainder = unsigned_number % 16;
    if (remainder < 10) {
      result += '0' + remainder;
    } else {
      result += 'A' + (remainder - 10);
    }
    unsigned_number /= 16;
  }

  if (is_negative) {
    result += '-';
  }

  std::reverse(result.begin(), result.end());
  return result;
}

int main() {
  int numb;

  while (true) {
    std::cout << "Input number: ";
    std::cin >> numb;
    std::cout << "This number in oct: " << oct(numb) << '\n';
    std::cout << "This number in hex: " << hex(numb) << '\n';
  }
  return 0;
}

