#include "FileWriter.h"
#include "VectorGenerator.h"
int main() {
  std::vector<int> vec = VectorGenerator::generate(20, -50, 100);
  FileWriter writer("output.txt");
  writer.process(vec);
  return 0;
}
