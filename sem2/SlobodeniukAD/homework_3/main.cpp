#include "text_processor.h"

int main() {
  const std::string kInputPath = "input.txt";
  const std::string kOutputPath = "output.txt";
  processTextFiles(kInputPath, kOutputPath);
  return 0;
}