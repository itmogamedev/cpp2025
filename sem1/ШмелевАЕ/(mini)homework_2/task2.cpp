#include <iostream>
int SiracuzHypothesis(int number) {
  if (number % 2 == 0) {
    return (number / 2);
  } else {
    return (number * 3 + 1);
  }
}
int main() {
  setlocale(LC_ALL, ("RU"));
  int number;
  std::cout << "¬ведите ваше число: ";
  std::cin >> number;
  while (number > 1) {
    number = SiracuzHypothesis(number);
    std::cout << number << "\n";
  }
}
