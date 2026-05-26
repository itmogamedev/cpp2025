#pragma once

#include <cstddef>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

class VectorProcessor {
 public:
  static constexpr std::size_t kVectorSize = 20;
  static constexpr int kMinRange = -50;
  static constexpr int kMaxRange = 100;

  explicit VectorProcessor(const std::string& output_path);

  void run();

 private:
  std::string output_path;
  std::vector<int> generated_vector;
  std::vector<int> sorted_vector;
  std::vector<int> filtered_vector;
  std::vector<int> unique_sorted_vector;
  int min_value;
  int max_value;
  std::ptrdiff_t positive_count;
  std::ptrdiff_t negative_count;
  std::ptrdiff_t zero_count;
  double average;

  void generateNumbers();
  void findMinMax();
  void sortAscending();
  void countSigns();
  void computeAverage();
  void removeEvens();
  void buildUniqueSorted();

  void writeReport() const;
};
