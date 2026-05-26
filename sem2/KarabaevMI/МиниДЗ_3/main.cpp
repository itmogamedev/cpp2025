#include "text_processor.h"

int main() {
  TextProcessor processor("input.txt", "output.txt");
  processor.run();
  return 0;
}
