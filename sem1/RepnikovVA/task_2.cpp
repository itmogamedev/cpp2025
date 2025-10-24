#include <iostream>
#include <string>

long long int syracuse(long long int num) {
  if (num == 1) {
    return num;
  } else if (num % 2 == 0) {
    return syracuse(num / 2);
  } else {
    return syracuse(((num * 3) + 1) / 2);
  }
}

int main() {
  setlocale(LC_ALL, "Russian");

  long long int num;
  std::cout << "Введите любое натуральное число: ";
  std::cin >> num;

  int res = syracuse(num);
  (res == 1)
      ? std::cout << "Результат: " << res << " => Теорема Сиракуза работает!"
      : std::cout << "Результат: " << res << " => Теорема не работает!";

  return 0;
}
