#include <iostream>

#include "parser.h"

int main() {
  setlocale(LC_ALL, "Russian");
  auto shops = Parser::parseFile("data.txt");
  for (const auto& shop : shops) {
    shop.printReport();
  }
  return 0;
}
