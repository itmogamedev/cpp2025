#include <iostream>
#include <locale>

#include "MagicItem.hpp"

int main() {
  setlocale(LC_ALL, "Russian");

  auto shops = readShopsFromFile("magic_shops.txt");

  if (shops.empty()) {
    std::cout << "Can't load data about shops\n";
    return 1;
  }

  for (const auto& shop : shops) {
    shop.printReport();
  }

  return 0;
}
