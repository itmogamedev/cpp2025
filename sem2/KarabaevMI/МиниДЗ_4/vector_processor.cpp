#include "vector_processor.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <utility>

VectorProcessor::VectorProcessor(const std::string& output_path)
    : output_path(output_path),
      min_value(0),
      max_value(0),
      positive_count(0),
      negative_count(0),
      zero_count(0),
      average(0.0) {}

void VectorProcessor::run() {
  generateNumbers();
  findMinMax();
  sortAscending();
  countSigns();
  computeAverage();
  removeEvens();
  buildUniqueSorted();
  writeReport();
  std::cout << "Done. See " << output_path << '\n';
}

void VectorProcessor::generateNumbers() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(kMinRange, kMaxRange);

  generated_vector.resize(kVectorSize);
  std::generate(generated_vector.begin(), generated_vector.end(),
                [&gen, &dist]() { return dist(gen); });
}

void VectorProcessor::findMinMax() {
  auto bounds =
      std::minmax_element(generated_vector.begin(), generated_vector.end());
  min_value = *bounds.first;
  max_value = *bounds.second;
}

void VectorProcessor::sortAscending() {
  sorted_vector = generated_vector;
  std::sort(sorted_vector.begin(), sorted_vector.end());
}

void VectorProcessor::countSigns() {
  positive_count = std::count_if(sorted_vector.begin(), sorted_vector.end(),
                                 [](int x) { return x > 0; });
  negative_count = std::count_if(sorted_vector.begin(), sorted_vector.end(),
                                 [](int x) { return x < 0; });
  zero_count = std::count_if(sorted_vector.begin(), sorted_vector.end(),
                             [](int x) { return x == 0; });
}

void VectorProcessor::computeAverage() {
  int sum = std::accumulate(sorted_vector.begin(), sorted_vector.end(), 0);
  average = static_cast<double>(sum) /
            static_cast<double>(sorted_vector.size());
}

void VectorProcessor::removeEvens() {
  filtered_vector = sorted_vector;
  filtered_vector.erase(
      std::remove_if(filtered_vector.begin(), filtered_vector.end(),
                     [](int x) { return x % 2 == 0; }),
      filtered_vector.end());
}

void VectorProcessor::buildUniqueSorted() {
  unique_sorted_vector = filtered_vector;
  std::sort(unique_sorted_vector.begin(), unique_sorted_vector.end());
  unique_sorted_vector.erase(
      std::unique(unique_sorted_vector.begin(), unique_sorted_vector.end()),
      unique_sorted_vector.end());
}

void VectorProcessor::writeReport() const {
  std::ofstream out(output_path);

  auto write_vec = [&out](const std::string& title,
                          const std::vector<int>& v) {
    out << title << '\n';
    if (v.empty()) {
      out << "  (empty)\n\n";
      return;
    }
    out << "  ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(out, " "));
    out << "\n\n";
  };

  write_vec("Generated vector (20 ints in [-50, 100]):", generated_vector);

  out << "Min: " << min_value << "\n";
  out << "Max: " << max_value << "\n\n";

  write_vec("Sorted ascending:", sorted_vector);

  out << "Positive count: " << positive_count << "\n";
  out << "Negative count: " << negative_count << "\n";
  out << "Zero count:     " << zero_count << "\n\n";

  out << "Average: " << average << "\n\n";

  write_vec("After removing even numbers (Variant 1):", filtered_vector);

  write_vec("Sorted unique values:", unique_sorted_vector);
}
