#include <iostream>

#include "file_reader.h"

int main() {
  std::cout << "=== Arcadia Merchant Guild Shop Analysis ===" << std::endl;

  std::vector<Shop> shops = FileReader::readFromFile("shops.txt");

  if (shops.empty()) {
    std::cout << "No shops found. Make sure shops.txt is in the correct "
                 "location."
              << std::endl;
    return 1;
  }

  for (const auto& shop : shops) {
    shop.analyze();
  }

  return 0;
}
