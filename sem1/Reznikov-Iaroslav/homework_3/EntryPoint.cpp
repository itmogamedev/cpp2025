#include <algorithm>
#include <iostream>
#include <vector>

#include "DataHolder.h"

int main() {
  DataHolder holder("Items.csv");
  for (const auto& elem : holder.getShops()) {
    elem->introduceSelf();
    elem->calculateStatistics();
    std::cout << "\n";
    std::cout << "----------------" << std::endl;
    std::cout << "\n";
  }
  return EXIT_SUCCESS;
}
