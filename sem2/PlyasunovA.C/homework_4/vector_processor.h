#ifndef VECTOR_PROCESSOR_H
#define VECTOR_PROCESSOR_H

#include <fstream>
#include <string>
#include <vector>

class VectorProcessor {
 public:
  void process();

 private:
  void generateVector();
  void findMinMax();
  void sortAndWrite();
  void countElements();
  void calculateAverage();
  void removeLessThanAverage();
  void createUniqueVector();

  void writeVector(const std::string& label, const std::vector<int>& vec);

  static const int kVectorSize = 20;
  static const int kMinValue = -50;
  static const int kMaxValue = 100;

  std::vector<int> numbers;
  double average = 0.0;
  std::ofstream output_file;
};

#endif  // VECTOR_PROCESSOR_H
