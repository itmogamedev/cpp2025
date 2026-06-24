#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

void runHomework4() {
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> dist(-50, 100);
  std::vector<int> vec(20);
  std::generate(vec.begin(), vec.end(), [&]() { return dist(gen); });

  std::ofstream out("output.txt");
  if (!out) {
    std::cerr << "Cannot open output.txt\n";
    return;
  }

  auto [min_it, max_it] = std::minmax_element(vec.begin(), vec.end());
  out << "Min: " << *min_it << " Max: " << *max_it << "\n";

  std::sort(vec.begin(), vec.end());
  out << "Sorted: ";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << "\n";

  int positive = std::count_if(vec.begin(), vec.end(), [](int x) { return x > 0; });
  int negative = std::count_if(vec.begin(), vec.end(), [](int x) { return x < 0; });
  int zero = std::count_if(vec.begin(), vec.end(), [](int x) { return x == 0; });
  out << "Positive: " << positive << ", Negative: " << negative << ", Zero: " << zero << "\n";

  double average = std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
  out << "Average: " << average << "\n";

  vec.erase(std::remove_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; }), vec.end());
  out << "After removing even: ";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << "\n";

  std::sort(vec.begin(), vec.end());
  std::vector<int> unique_vec;
  std::unique_copy(vec.begin(), vec.end(), std::back_inserter(unique_vec));
  out << "Unique sorted: ";
  std::copy(unique_vec.begin(), unique_vec.end(), std::ostream_iterator<int>(out, " "));
  out << "\n";
}

int main() {
  runHomework4();
  return 0;
}