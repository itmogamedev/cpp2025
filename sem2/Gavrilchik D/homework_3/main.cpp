#include <windows.h>
#include "text_processor.h"

int main() {
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
  TextProcessor processor("input.txt", "output.txt");
  processor.run();
  return 0;
}