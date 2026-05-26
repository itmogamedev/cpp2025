#include "../Header Files/number_processor.h"

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

namespace homework {

namespace {

// Helper that prints a vector of ints to the stream without using any
// for / while loops. Uses std::for_each on the tail of the vector so that
// commas are placed correctly between elements.
void writeVector(std::ofstream& out, const std::string& title,
                 const std::vector<int>& vec) {
  out << title << " (size = " << vec.size() << "): [";
  if (!vec.empty()) {
    out << vec.front();
    std::for_each(vec.begin() + 1, vec.end(),
                  [&out](int v) { out << ", " << v; });
  }
  out << "]\n\n";
}

}  // namespace

void runHomework(const std::string& output_filename) {
  std::ofstream out(output_filename);
  out << "===== Mini-homework 4 (Variant 1) =====\n\n";

  // 1. Generate a vector of 20 integers in [-50, 100] using std::generate
  //    and std::mt19937.
  std::vector<int> numbers(20);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);
  std::generate(numbers.begin(), numbers.end(),
                [&gen, &dist]() { return dist(gen); });
  writeVector(out, "1. Generated vector", numbers);

  // 2. Find min / max.
  auto min_max = std::minmax_element(numbers.begin(), numbers.end());
  out << "2. Minimum: " << *min_max.first << "\n";
  out << "   Maximum: " << *min_max.second << "\n\n";

  // 3. Sort ascending.
  std::sort(numbers.begin(), numbers.end());
  writeVector(out, "3. Sorted vector", numbers);

  // 4. Count positive / negative / zero elements.
  auto positive_count =
      std::count_if(numbers.begin(), numbers.end(),
                    [](int v) { return v > 0; });
  auto negative_count =
      std::count_if(numbers.begin(), numbers.end(),
                    [](int v) { return v < 0; });
  auto zero_count =
      std::count_if(numbers.begin(), numbers.end(),
                    [](int v) { return v == 0; });
  out << "4. Positive count: " << positive_count << "\n";
  out << "   Negative count: " << negative_count << "\n";
  out << "   Zero count:     " << zero_count << "\n\n";

  // 5. Arithmetic mean.
  double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
  double mean =
      numbers.empty() ? 0.0 : sum / static_cast<double>(numbers.size());
  out << "5. Arithmetic mean: " << mean << "\n\n";

  // 6. Variant 1: remove all even numbers.
  numbers.erase(
      std::remove_if(numbers.begin(), numbers.end(),
                     [](int v) { return v % 2 == 0; }),
      numbers.end());
  writeVector(out, "6. After removing even numbers", numbers);

  // 7. Sort the resulting vector and build a new one with unique values.
  std::sort(numbers.begin(), numbers.end());
  std::vector<int> unique_numbers;
  std::unique_copy(numbers.begin(), numbers.end(),
                   std::back_inserter(unique_numbers));
  writeVector(out, "7. Sorted unique values", unique_numbers);
}

}  // namespace homework
