#include <iostream>

int main()
{
  setlocale(LC_ALL, "ru");
  int a;
  std::cin >> a;
  while (a != 1) {
    std::cout << a << "-";
    if (a % 2 == 0) {
      a = a / 2;
    }
    else {
      a = ((a * 3) + 1) / 2;
    }
  }
  std::cout << "1" << std:: endl;
}
