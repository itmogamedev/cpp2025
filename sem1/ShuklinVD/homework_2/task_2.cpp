#include <iostream>
#include <locale>
bool checkHypotesis(int num) {
  if (num < 1) {
    return false;
  }
  while (num != 1) {
    if (num % 2 == 0) {
      num /= 2;
      // std::cout << num << '\n'; - код для того, чтобы разработчик мог увидеть
      // ход действий
    } else {
      num = (num * 3 + 1) / 2;
      // std::cout << num << '\n'; - код для того, чтобы разработчик мог увидеть
      // ход действий
    }
  }
  return true;
}
int main() {
  setlocale(LC_ALL, "");
  int input;
  std::cout << "введите натуральное число: ";
  std::cin >> input;
  if (checkHypotesis(input)) {
    std::cout << "всё хорошо";
  } else {
    std::cout << "кто-то ввёл не натуральное число";
  }

  return 0;
}
