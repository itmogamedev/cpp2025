#include <algorithm>
#include <numeric>
#include <fstream>
#include <random>
#include <vector>

void solve() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(-50, 100);
  std::vector<int> v(20);
  std::generate(v.begin(), v.end(), [&]() {return dist(gen); });

  int _min = *std::min_element(v.begin(), v.end());
  int _max = *std::max_element(v.begin(), v.end());

  std::vector<int> sorted_v = v;
  std::sort(sorted_v.begin(), sorted_v.end());

  int zero_count = std::count(v.begin(), v.end(), 0);
  int positive_count = std::count_if(v.begin(), v.end(), [](int x) { return x > 0; });
  int negative_count = std::count_if(v.begin(), v.end(), [](int x) {return x < 0;});

  float average = std::accumulate(v.begin(), v.end(), 0.0) / v.size();

  std::vector<int> less_average_v = v;
  less_average_v.erase(std::remove_if(less_average_v.begin(), less_average_v.end(), [average](int x) { return x >= average; }), less_average_v.end());

  std::vector<int> unique_v = v;
  std::sort(unique_v.begin(), unique_v.end());
  auto last = std::unique(unique_v.begin(), unique_v.end());
  unique_v.erase(last, unique_v.end());

  std::ofstream file_output("output.txt");
  file_output << "Original vector: ";
  std::copy(v.begin(), v.end(),
      std::ostream_iterator<int>(file_output, " "));
  file_output << "\nMinimum: " << _min << "\nMaximum: " << _max << std::endl;
  file_output << "Sorted vector: ";
  std::copy(sorted_v.begin(), sorted_v.end(),
	  std::ostream_iterator<int>(file_output, " "));
  file_output << "\nZero count: " << zero_count << "\nPositive count: " << positive_count << "\nNegative count: " << negative_count << std::endl;
  file_output << "Average: " << average << std::endl;
  file_output << "Elements less than average: ";
  std::copy(less_average_v.begin(), less_average_v.end(),
	  std::ostream_iterator<int>(file_output, " "));
  file_output << "\nUnique elements: ";
  std::copy(unique_v.begin(), unique_v.end(),
	  std::ostream_iterator<int>(file_output, " "));
}

int main() {
  solve();

  return 0;
}
