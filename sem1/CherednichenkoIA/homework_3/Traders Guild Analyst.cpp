#include <iostream>

#include "shop_processor.h"
#include "shop_reader.h"

int main() {
  setlocale(LC_ALL, "Russian");
  auto shops = readShopsFromFile("input.txt");
  processShops(shops);
  return 0;
}
