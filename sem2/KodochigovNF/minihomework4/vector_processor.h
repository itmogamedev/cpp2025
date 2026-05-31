#ifndef VECTOR_PROCESSOR_H
#define VECTOR_PROCESSOR_H

#include <string>
#include <vector>

class VectorProcessor {
 public:
  void run();

 private:
  void process();

  void writeResults(const std::string& filename) const;

  static void writeVector(std::ofstream& out, const std::string& caption,
                          const std::vector<int>& vec);

  static const int kVectorSize;
  static const int kMinValue;
  static const int kMaxValue;
  static const std::string kOutputFile;

  std::vector<int> original;
  int min_value = 0;
  int max_value = 0;
  std::vector<int> sorted;
  int positive_count = 0;
  int negative_count = 0;
  int zero_count = 0;
  double average = 0.0;
  std::vector<int> after_evens_removed;
  std::vector<int> unique_values;
};

#endif
