#include "vector_processor.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>

const int VectorProcessor::kVectorSize = 20;
const int VectorProcessor::kMinValue = -50;
const int VectorProcessor::kMaxValue = 100;
const std::string VectorProcessor::kOutputFile = "output.txt";

void VectorProcessor::run() {
  process();
  writeResults(kOutputFile);
}

void VectorProcessor::process() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(kMinValue, kMaxValue);

  original.resize(kVectorSize);
  std::generate(original.begin(), original.end(),
                [&gen, &dist]() mutable { return dist(gen); });

  std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>
      minmax = std::minmax_element(original.begin(), original.end());
  min_value = *(minmax.first);
  max_value = *(minmax.second);

  sorted = original;
  std::sort(sorted.begin(), sorted.end());

  positive_count = static_cast<int>(std::count_if(
      original.begin(), original.end(), [](int x) { return x > 0; }));
  negative_count = static_cast<int>(std::count_if(
      original.begin(), original.end(), [](int x) { return x < 0; }));
  zero_count = static_cast<int>(std::count_if(original.begin(), original.end(),
                                              [](int x) { return x == 0; }));

  double sum = std::accumulate(original.begin(), original.end(), 0.0);
  average = sum / original.size();

  after_evens_removed = original;
  auto new_end =
      std::remove_if(after_evens_removed.begin(), after_evens_removed.end(),
                     [](int x) { return x % 2 == 0; });
  after_evens_removed.erase(new_end, after_evens_removed.end());

  std::vector<int> sorted_after_evens = after_evens_removed;
  std::sort(sorted_after_evens.begin(), sorted_after_evens.end());
  auto last = std::unique(sorted_after_evens.begin(), sorted_after_evens.end());
  sorted_after_evens.erase(last, sorted_after_evens.end());
  unique_values = sorted_after_evens;
}

void VectorProcessor::writeVector(std::ofstream& out,
                                  const std::string& caption,
                                  const std::vector<int>& vec) {
  out << caption << ":\n";
  std::for_each(vec.begin(), vec.end(), [&out](int n) { out << n << ' '; });
  out << "\n\n";
}

void VectorProcessor::writeResults(const std::string& filename) const {
  std::ofstream out(filename);
  if (!out) {
    std::cerr << "Cannot open output file." << std::endl;
    return;
  }

  writeVector(out, "Original vector", original);

  out << "Minimum: " << min_value << "\n";
  out << "Maximum: " << max_value << "\n\n";

  writeVector(out, "Sorted vector", sorted);

  out << "Positive count: " << positive_count << "\n";
  out << "Negative count: " << negative_count << "\n";
  out << "Zero count: " << zero_count << "\n\n";

  out << "Average: " << average << "\n\n";

  writeVector(out, "After removing even numbers (Variant 1)",
              after_evens_removed);

  writeVector(out, "Unique values (sorted, duplicates removed)", unique_values);
}
