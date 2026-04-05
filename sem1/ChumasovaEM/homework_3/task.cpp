#include <windows.h>

#include <fstream>
#include <iostream>

#include "MagicItems.h"

void processShops() {
  std::ifstream file("stores.txt");
  if (!file.is_open()) {
    std::cerr << "Файл 'stores.txt' не найден!\n";
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.find("Магазин:") != std::string::npos) {
      std::string shopName = line.substr(8);
      auto items = readShop(file, shopName);
      shopStats stats = calculateStats(shopName, items);
      printStats(stats);
    }
  }
}

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  processShops();
  return 0;
}
