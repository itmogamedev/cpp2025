
#include <iostream>

#include "string_analize.h"

int main() {
  std::setlocale(LC_ALL, "Russian");
  int threshold = 0;
  std::string search_word;
  std::cout << "Введите порог длины и слово для поиска: ";
  std::cin >> threshold >> search_word;
  StringAnalize sa;
  sa.processFiles("input.txt", "output.txt", threshold, search_word);
  return 0;
}
