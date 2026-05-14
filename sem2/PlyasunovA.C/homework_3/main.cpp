#include <clocale>

#include "text_processor.h"

int main() {
  std::setlocale(LC_ALL, "Russian");
  run();
  return 0;
}
