#include <iostream>
#include <string>
std::string hypTest(int num, std::string res) {
  int count = 0;
  while (num != 1 and count < 1000) {
    count++;
    if (num % 2 == 0) {
      num /= 2;
    } else {
      num *= 3;
      num = (num + 1) / 2;
    }
  }
  if (num == 1) {
    res = "true";
  } else {
    res = "false";
  }
  return res;
}
int main() {
  std::cout << "Type a natural number:" << std::endl;
  float number = 0;
  std::string result = "questionable";
  std::cin >> number;
  if (number <= 0 or number != int(number)) {
    return 0;
  }
  result = hypTest(number, result);
  std::cout << "The Sirkakuz hypothesis is " + result;
}
