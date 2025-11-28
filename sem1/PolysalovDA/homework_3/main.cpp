#include <iostream>
#include <vector>

#include "FileReader.h"

int main() {
  std::vector<Shop*> shops = readShopsFromFile("shops.txt");

  for (const auto& shop : shops) {
    shop->printStats();
  }

  for (auto shop : shops) {
    delete shop;
  }

  return 0;
}