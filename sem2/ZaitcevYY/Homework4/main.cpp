#include <algorithm>
#include <fstream>
#include <functional>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

int main() {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(-50, 100);
  std::vector<int> V(20);
  std::generate(V.begin(), V.end(), [&]() { return dist(rng); });

  std::ofstream out("output.txt");
  out << "Start: " << std::endl;
  std::copy(V.begin(), V.end(), std::ostream_iterator<int>(out, " "));
  out << std::endl;

  auto [min_item, max_item] = std::minmax_element(V.begin(), V.end());
  out << "Min: " << *min_item << std::endl;
  out << "Max: " << *max_item << std::endl;
  std::sort(V.begin(), V.end());
  out << "Sorted: " << std::endl;
  std::copy(V.begin(), V.end(), std::ostream_iterator<int>(out, " "));
  out << std::endl;

  int positive_count = static_cast<int>(std::count_if(V.begin(), V.end(), [](int x) { return x > 0; }));
  int negative_count = static_cast<int>(std::count_if(V.begin(), V.end(), [](int x) { return x < 0; }));
  int zero_count = static_cast<int>(std::count(V.begin(), V.end(), 0));
  out << "Positive: " << positive_count << std::endl;
  out << "Negative: " << negative_count << std::endl;
  out << "Zero: " << zero_count << std::endl;

  float avg = static_cast<float>(std::accumulate(V.begin(), V.end(), 0)) / V.size();
  out << "Average: " << avg << std::endl;

  V.erase(std::remove_if(V.begin(), V.end(), [avg](int x) { return x < avg; }), V.end());
  out << "After deleting all those less than average: " << std::endl;
  std::copy(V.begin(), V.end(), std::ostream_iterator<int>(out, " "));
  out << std::endl;
  std::vector<int> Uniq;
  Uniq.reserve(V.size());
  std::unique_copy(V.begin(), V.end(), std::back_inserter(Uniq));
  out << "Only unique values" << std::endl;
  std::copy(Uniq.begin(), Uniq.end(), std::ostream_iterator<int>(out, " "));
  out << std::endl;

  out.close();
  return 0;
}