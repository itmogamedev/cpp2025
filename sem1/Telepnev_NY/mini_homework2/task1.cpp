#include <algorithm>
#include <iostream>
#include <string>

void printConversionResults(int number);
std::string toOctal(int decimalValue);
std::string toHexadecimal(int decimalValue);

int main() {
  setlocale(LC_ALL, "ru");
  int userNumber;
  std::string continueChoice;

  do {
    std::cout << "Введите целое число для преобразования: ";
    std::cin >> userNumber;

    printConversionResults(userNumber);

    std::cout << "Хотите преобразовать еще одно число? (да/нет): ";
    std::cin >> continueChoice;

  } while (continueChoice == "да");

  std::cout << "Программа завершена." << std::endl;

  return 0;
}

std::string toHexadecimal(int decimalValue) {
  if (decimalValue == 0) return "0";

  const std::string hexDigits = "0123456789ABCDEF";
  bool isNegative = decimalValue < 0;
  unsigned int absoluteValue = isNegative ? -decimalValue : decimalValue;

  std::string result;
  while (absoluteValue > 0) {
    result += hexDigits[absoluteValue % 16];
    absoluteValue /= 16;
  }
  if (isNegative) result += '-';

  std::reverse(result.begin(), result.end());
  return result;
}

std::string toOctal(int decimalValue) {
  if (decimalValue == 0) return "0";

  const std::string octalDigits = "01234567";
  bool isNegative = decimalValue < 0;
  unsigned int absoluteValue = isNegative ? -decimalValue : decimalValue;

  std::string result;
  while (absoluteValue > 0) {
    result += octalDigits[absoluteValue % 8];
    absoluteValue /= 8;
  }
  if (isNegative) result += '-';

  std::reverse(result.begin(), result.end());
  return result;
}

void printConversionResults(int number) {
  std::cout << "_______________Результат_______________" << std::endl;
  std::cout << "Десятичное число: " << number << std::endl;
  std::cout << "Шестнадцатеричное представление: " << toHexadecimal(number)
            << std::endl;
  std::cout << "Восьмеричное представление: " << toOctal(number) << std::endl;
  std::cout << "_______________________________________" << std::endl;
}
