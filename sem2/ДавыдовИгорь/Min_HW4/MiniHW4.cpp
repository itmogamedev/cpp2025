#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

void vec_generate(std::vector<int>& vec, std::ostream& out) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);
  std::generate(vec.begin(), vec.end(), [&]() { return dist(gen); });

  out << "1. vec:\n";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << "\n";
}

void vec_minmax(const std::vector<int>& vec, std::ostream& out) {
  auto minmax = std::minmax_element(vec.begin(), vec.end());
  out << "2. min: " << *minmax.first << "\n";
  out << "   max: " << *minmax.second << "\n";
}

void vec_sort(std::vector<int>& vec, std::ostream& out) {
  std::sort(vec.begin(), vec.end());
  out << "3. sorted:\n";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << "\n";
}

void vec_count(const std::vector<int>& vec, std::ostream& out) {
  long long positive_cnt =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x > 0; });
  long long negative_cnt =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x < 0; });
  long long zero_cnt =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x == 0; });

  out << "4. pos: " << positive_cnt << "\n";
  out << "   neg: " << negative_cnt << "\n";
  out << "   zero: " << zero_cnt << "\n";
}

double vec_average(const std::vector<int>& vec, std::ostream& out) {
  double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
  double average = sum / vec.size();
  out << "5. avrageе: " << average << "\n";
  return average;
}

void vec_without_average(std::vector<int>& vec, double average,
                         std::ostream& out) {
  vec.erase(std::remove_if(vec.begin(), vec.end(),
                           [average](int x) { return x < average; }),
            vec.end());

  out << "6. vector after removing elements lower than average:\n";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << "\n";
}

void vec_unique(std::vector<int>& vec, std::ostream& out) {
  std::sort(vec.begin(), vec.end());
  std::vector<int> unique_vec;
  std::unique_copy(vec.begin(), vec.end(), std::back_inserter(unique_vec));

  out << "7. vec with unique elements:\n";
  std::copy(unique_vec.begin(), unique_vec.end(),
            std::ostream_iterator<int>(out, " "));
  out << "\n";
}

int main() {
  std::ofstream out("output.txt");
  std::vector<int> vec(20);
  vec_generate(vec, out);
  vec_minmax(vec, out);
  vec_sort(vec, out);
  vec_count(vec, out);
  double average = vec_average(vec, out);
  vec_without_average(vec, average, out);
  vec_unique(vec, out);
  out.close();
}
