#include <format>
#include <iostream>
#include <locale>

int syracuseFunc(int num_input);

int main() {
  std::setlocale(LC_CTYPE, "Russian");
  int input_int = 0;

  std::cout << "Введите число натуральное число: ";
  std::cin >> input_int;
  std::cout << "После преобразований мы получили число: " << syracuseFunc(input_int);

  return 0;
}

int syracuseFunc(int func_int) {
  while (func_int != 1) {
    if (func_int % 2 == 0) {
      func_int = func_int / 2;
    } else {
      func_int = func_int * 3;
      func_int += 1;
      func_int = func_int / 2;
    }
  }
  return func_int;
}
