#include <iostream>

// Задача 2:
// Реализовать программу, которая проверяет гипотезу Сиракуз.
// Суть гипотезы:
// Возьмем любое натуральное число.
// Если оно четное - разделим его пополам, если нечетное - умножим на 3, прибавим 1 и разделим пополам.
// Повторим эти действия с вновь полученным числом.
// Гипотеза гласит, что независимо от выбора первого числа рано или поздно мы получим 1.


bool сheckSyracuseHypothesis(int number) {
  if (number <= 0){
    return false;
  }

  while (number != 1){
    if (number % 2 == 0) {
      number /= 2;
    } else {
      number = (3 * number + 1)/2;
    }     
  }

  return number == 1;
}

int main() {
    int user_number;
    std::cout << "Введите свое натуральное число для проверки гипотезы: ";
    std::cin >> user_number;

    bool user_res = сheckSyracuseHypothesis(user_number);

    std::string res;

    if (user_res == 1){
      res = "Да";
    } else {
      res = "Нет";
    }

    std::cout << "Выполнилась ли гипотеза? : " << res << std::endl;
    return 0;
}