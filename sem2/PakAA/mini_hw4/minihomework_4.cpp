#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <string>
#include <vector>

namespace {

void writeIntVector(std::ofstream& out, const std::vector<int>& vec,
                    const std::string& label) {
  out << label << ": ";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << "\n";
}

std::vector<int> generateRandomVector(std::size_t size, int min_val,
                                      int max_val) {
  std::vector<int> v(size);
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(min_val, max_val);
  std::generate(v.begin(), v.end(), [&rng, &dist]() { return dist(rng); });
  return v;
}

void writeMinMax(std::ofstream& out, const std::vector<int>& vec) {
  auto minmax = std::minmax_element(vec.begin(), vec.end());
  out << "Min: " << *minmax.first << "\n";
  out << "Max: " << *minmax.second << "\n";
}

void writeCounts(std::ofstream& out, const std::vector<int>& vec) {
  auto positive =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x > 0; });
  auto negative =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x < 0; });
  auto zeros =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x == 0; });
  out << "Positive: " << positive << "\n";
  out << "Negative: " << negative << "\n";
  out << "Zero: " << zeros << "\n";
}

double computeMean(const std::vector<int>& vec) {
  return std::accumulate(vec.begin(), vec.end(), 0.0) /
         static_cast<double>(vec.size());
}

std::vector<int> removeBelowMean(std::vector<int> vec, double mean) {
  vec.erase(std::remove_if(vec.begin(), vec.end(),
                           [mean](int x) { return x < mean; }),
            vec.end());
  return vec;
}

std::vector<int> sortedUniqueCopy(std::vector<int> vec) {
  std::sort(vec.begin(), vec.end());
  vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
  return vec;
}

void runHomework(std::ofstream& out) {
  auto vec = generateRandomVector(20, -50, 100);
  writeIntVector(out, vec, "Vector");
  writeMinMax(out, vec);
  std::sort(vec.begin(), vec.end());
  writeIntVector(out, vec, "Sorted");
  writeCounts(out, vec);
  double mean = computeMean(vec);
  out << "Mean: " << std::fixed << std::setprecision(2) << mean << "\n";
  auto filtered = removeBelowMean(vec, mean);
  writeIntVector(out, filtered, "Filtered");
  auto unique_sorted = sortedUniqueCopy(filtered);
  writeIntVector(out, unique_sorted, "Unique");
}

}  // namespace

int main() {
  std::ofstream output("output.txt");
  if (!output.is_open()) {
    std::cerr << "Error: cannot open output.txt\n";
    return 1;
  }
  runHomework(output);
  return 0;
}
