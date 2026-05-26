#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

void solve() {
  std::ofstream f("output.txt");
  std::vector<int> v(20);
  std::mt19937 g(std::random_device{}());
  std::uniform_int_distribution<> d(-50, 100);

  std::generate(v.begin(), v.end(), [&]() { return d(g); });
  auto [mi, ma] = std::minmax_element(v.begin(), v.end());
  f << "Min: " << *mi << "\nMax: " << *ma << "\n";

  std::sort(v.begin(), v.end());
  f << "Sorted: ";
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(f, " "));
  f << "\nPos: "
    << std::count_if(v.begin(), v.end(), [](int x) { return x > 0; });
  f << "\nNeg: "
    << std::count_if(v.begin(), v.end(), [](int x) { return x < 0; });
  f << "\nZero: "
    << std::count_if(v.begin(), v.end(), [](int x) { return x == 0; });

  double a = std::accumulate(v.begin(), v.end(), 0.0) / v.size();
  f << "\nAvg: " << a << "\n";
  v.erase(std::remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }),
          v.end());
  f << "No evens: ";
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(f, " "));

  std::sort(v.begin(), v.end());
  std::vector<int> u;
  std::unique_copy(v.begin(), v.end(), std::back_inserter(u));
  f << "\nUnique: ";
  std::copy(u.begin(), u.end(), std::ostream_iterator<int>(f, " "));
}

int main() {
  solve();
  return 0;
}