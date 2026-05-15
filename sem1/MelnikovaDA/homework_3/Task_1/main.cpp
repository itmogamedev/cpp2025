#include <windows.h>

#include <iostream>
#include <locale>
#include <vector>

#include "FileReader.h"
#include "Shop.h"

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  std::setlocale(LC_ALL, "Russian");

  std::vector<shop> shops = fileReader::readShopsFromFile("data.txt");

  for (const auto& shop : shops) {
    shop.analyzeShop();
  }

  return 0;
}
