//запуск программы
#include <windows.h>
#include "shop_processor.h"

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  ShopProcessor::processFile("items.txt");
  return 0;
}
