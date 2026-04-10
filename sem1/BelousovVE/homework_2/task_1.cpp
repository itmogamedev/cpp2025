#include <string>

using std::string;

int NumToBase(int num, int base) {
  if (num <= 0) return 0;

  string result;

  while (num > 0) {
    result = std::to_string(num % base) + result;
    num /= base;
  }

  return std::stoi(result);
}
