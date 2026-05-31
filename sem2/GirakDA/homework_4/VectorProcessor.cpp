#include "VectorProcessor.h"

#include <algorithm>
#include <numeric>

VectorProcessor::Stats VectorProcessor::calculateStats(
    const std::vector<int>& vec) {
  Stats stats;
  auto minmax = std::minmax_element(vec.begin(), vec.end());
  stats.min = *minmax.first;
  stats.max = *minmax.second;
  stats.positive =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x > 0; });
  stats.negative =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x < 0; });
  stats.zero = std::count(vec.begin(), vec.end(), 0);
  stats.average = std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
  return stats;
}

void VectorProcessor::sortVector(std::vector<int>& vec) {
  std::sort(vec.begin(), vec.end());
}

void VectorProcessor::removeEvenNumbers(std::vector<int>& vec) {
  auto newEnd =
      std::remove_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; });
  vec.erase(newEnd, vec.end());
}

std::vector<int> VectorProcessor::getUniqueSorted(const std::vector<int>& vec) {
  std::vector<int> result = vec;
  std::sort(result.begin(), result.end());
  auto last = std::unique(result.begin(), result.end());
  result.erase(last, result.end());
  return result;
}
