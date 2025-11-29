#include <locale>

#include "FileReader.h"
#include "Stats.h"

int main() {
  setlocale(LC_ALL, "");
  auto shops = readShops("shops.txt");

  for (auto& s : shops) printShopStats(s);

  return 0;
}
