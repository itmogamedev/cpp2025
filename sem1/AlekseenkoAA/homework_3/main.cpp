// main.cpp : ДЛЯ КОМПЛИЛЯЦИИ ПРОГРАММЫ ИСПОЛЬЗОВАТЬ C++ 20!

#include <iostream>
#include <vector>

#include "file_reader.h"
#include "shop.h"

int main() {
  const std::string filename = "shops_data.txt";

  try {
    std::vector<Shop> shops = readShopsFromFile(filename);
    for (const Shop& shop : shops) {
      shop.printReport();
    }
  } catch (const std::exception& ex) {
    std::cout << "Ошибка: " << ex.what() << "\n";
    return 1;
  }

  return 0;
}
