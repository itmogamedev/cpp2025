#include <cassert>
#include <iostream>
#include <string>

std::string from10toN(std::string, int);
std::string from10toN(int, int);
void syracuseHypothesis(int num);

int main() {
  int numForHypothesis;
  std::cout << "Enter number to check the Syracuse hypothesis: ";
  std::cin >> numForHypothesis;
  syracuseHypothesis(numForHypothesis);

  // for(int i = 0; i < 50; i++){
  //     std::cout << "10b: " << i << ", 8b: "<< From10toN(i, 8) << ", 16b: "<<
  //     From10toN(i, 16) <<std::endl;
  // }
  return 0;
}

void syracuseHypothesis(int num) {
  if (num <= 0) {
    std::cerr << "Number must be positive." << std::endl;
    return;
  }
  std::cout << num << "->";
  while (num > 1) {
    if (num % 2 == 0) {
      num = num / 2;
    } else {
      num = ((num * 3) + 1) / 2;
    }
    if (num == 1) {
      std::cout << num << std::endl;
    } else {
      std::cout << num << "->";
    }
  }
}

// Converts number from base 10 to base N.
std::string from10toN(std::string snum10, int n) {
  assert(n <= 16);
  std::string symbols[16] = {"0", "1", "2", "3", "4", "5", "6", "7",
                             "8", "9", "A", "B", "C", "D", "E", "F"};
  int inum10 = std::stoi(snum10);
  std::string snum_n = "";
  do {
    snum_n = symbols[(inum10 % n)] + snum_n;
    inum10 = inum10 / n;
  } while (inum10 > 0);

  return snum_n;
}

std::string from10toN(int inum10, int n) {
  return from10toN(std::to_string(inum10), n);
}

int convertStringToInt(std::string str) { return std::stoi(str); }
