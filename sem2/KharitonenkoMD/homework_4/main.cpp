#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

void printVector(std::ofstream& out, const std::string& title,
                 const std::vector<int>& v) {
  out << title << "\n  ";
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(out, " "));
  out << "\n\n";
}

int main() {
  std::ofstream out("output.txt");
  if (!out.is_open()) {
    std::cerr << "Сould not open output.txt\n";
    return 1;
  }

  std::vector<int> v(20);
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(-50, 100);
  std::generate(v.begin(), v.end(), [&]() { return dist(rng); });

  printVector(out, " Generated vector ", v);

  auto minIt = std::min_element(v.begin(), v.end());
  auto maxIt = std::max_element(v.begin(), v.end());
  out << " Min and Max \n";
  out << "  Min: " << *minIt << "\n";
  out << "  Max: " << *maxIt << "\n\n";

  std::sort(v.begin(), v.end());
  printVector(out, " Sorted vector (ascending) ", v);

  int negCount = static_cast<int>(
      std::count_if(v.begin(), v.end(), [](int x) { return x < 0; }));
  int zeroCount = static_cast<int>(std::count(v.begin(), v.end(), 0));
  int posCount = static_cast<int>(
      std::count_if(v.begin(), v.end(), [](int x) { return x > 0; }));

  out << " Element counts \n";
  out << "  Negative: " << negCount << "\n";
  out << "  Zero:     " << zeroCount << "\n";
  out << "  Positive: " << posCount << "\n\n";

  double mean =
      static_cast<double>(std::accumulate(v.begin(), v.end(), 0)) / v.size();
  out << " Arithmetic mean \n";
  out << "  " << mean << "\n\n";

  v.erase(
      std::remove_if(v.begin(), v.end(), [mean](int x) { return x < mean; }),
      v.end());
  printVector(out, " After removing elements below mean ", v);

  std::sort(v.begin(), v.end());
  std::vector<int> unique_v;
  std::unique_copy(v.begin(), v.end(), std::back_inserter(unique_v));
  printVector(out, " Sorted unique values ", unique_v);

  out.close();
  std::cout << "Results are in output.txt\n";
  return 0;
}
