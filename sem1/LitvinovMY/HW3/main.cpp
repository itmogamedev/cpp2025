#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "MagicItem.h"
#include "Store.h"

int main() {
  std::vector<Store> stores;

  std::ifstream f("stores.txt");
  std::string line;
  char expect_whitespace;
  while (std::getline(f, line)) {
    std::stringstream ss(line);
    ss >> std::noskipws;
    std::string first;
    if (ss >> first) {
      if (first == "Магазин:") {
        std::string new_store;
        ss >> expect_whitespace >> new_store;
        stores.push_back(Store(new_store));
      } else {
        stores[stores.size() - 1].AddItem(ProcessItem(first, &ss));
      }
    }
  }

  for (auto store : stores) {
    std::cout << store.PrintStatistics() << std::endl;
  }

  return 0;
}