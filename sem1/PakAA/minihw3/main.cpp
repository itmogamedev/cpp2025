#include "parser.h"

int main() {
  auto shops = Parser::parseFile("data.txt");
  for (const auto& shop : shops) {
    shop.printReport();
  }
  return 0;
}
