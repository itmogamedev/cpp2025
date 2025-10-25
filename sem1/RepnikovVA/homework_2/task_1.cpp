#include <iostream>
#include <string>

std::string octAndHex(int num) {
  std::string result;
  std::string str_8, str_16;

  int num_8 = num, num_16 = num;
  char alph[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  while (num_8 > 0) {
    std::string elem_8 = std::to_string(num_8 % 8);
    str_8 = elem_8 + str_8;
    num_8 /= 8;
  }
  while (num_16 > 0) {
    char elem_16 = alph[num_16 % 16];
    str_16 = elem_16 + str_16;
    num_16 /= 16;
  }

  result = "Восьмеричная: " + str_8 + ";" + " Шестнадцатеричная: " + str_16;

  return result;
}

int main() {
  setlocale(LC_ALL, "Russian");

  int num;
  std::cout << "Введите число: ";
  std::cin >> num;

  std::string res = octAndHex(num);
  std::cout << res;

  return 0;
}
