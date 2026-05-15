#include <iostream>

int sirakuz(int num) {
  int count = 0;
  while (num != 1) {
    if (num % 2 == 0) {
      num /= 2;
    } else {
      num *= 3;
      num += 1;
      num /= 2;
    }
    count++;
  }
  return count;
}

int main() {
  int num;
  std::cout << "Enter the number: ";
  std::cin >> num;
  std::cout << "To get 1 from " << num << " you need " << sirakuz(num)
            << " times use Sirakuz";
}