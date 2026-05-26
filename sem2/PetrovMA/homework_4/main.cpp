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

  std::vector<int> vec(20);
  std::generate(vec.begin(), vec.end(), [&]() { return dist(rng); });

  std::ofstream out("output.txt");

  out << "initial: " << std::endl;
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << std::endl;

  auto [min_item, max_item] = std::minmax_element(vec.begin(), vec.end());

  out << "min: " << *min_item << std::endl;
  out << "max: " << *max_item << std::endl;

  std::sort(vec.begin(), vec.end());

  out << "sorted: " << std::endl;
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << std::endl;

  int positive_count = static_cast<int>(std::count_if(vec.begin(), vec.end(), [](int x) { return x > 0; }));
  int negative_count = static_cast<int>(std::count_if(vec.begin(), vec.end(), [](int x) { return x < 0; }));
  int zero_count = static_cast<int>(std::count(vec.begin(), vec.end(), 0));

  out << "positive: " << positive_count << std::endl;
  out << "negative: " << negative_count << std::endl;
  out << "zero: " << zero_count << std::endl;

  float avg = static_cast<float>(std::accumulate(vec.begin(), vec.end(), 0)) / vec.size();

  out << "average: " << avg << std::endl;

  vec.erase(std::remove_if(vec.begin(), vec.end(), [avg](int x) { return x < avg; }), vec.end());

  out << "after deleting less than average: " << std::endl;
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << std::endl;

  std::vector<int> uniques;
  uniques.reserve(vec.size());
  std::unique_copy(vec.begin(), vec.end(), std::back_inserter(uniques));

  out << "only unique values" << std::endl;
  std::copy(uniques.begin(), uniques.end(), std::ostream_iterator<int>(out, " "));
  out << std::endl;

  out.close();
  return 0;
}
