#include <algorithm>
#include <fstream>
#include <numeric>
#include <random>
#include <vector>

int main() {
  std::ofstream out("output.txt");

  std::vector<int> v(20);
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> dist(-50, 100);
  std::generate(v.begin(), v.end(), [&]() { return dist(gen); });

  std::for_each(v.begin(), v.end(), [&](int x) { out << x << " "; });
  out << "\n\n";

  out << "Min: " << *std::min_element(v.begin(), v.end()) << "\n";
  out << "Max: " << *std::max_element(v.begin(), v.end()) << "\n\n";

  std::sort(v.begin(), v.end());
  std::for_each(v.begin(), v.end(), [&](int x) { out << x << " "; });
  out << "\n\n";

  out << "Pos: " << std::count_if(v.begin(), v.end(), [](int x) { return x > 0; }) << "\n";
  out << "Neg: " << std::count_if(v.begin(), v.end(), [](int x) { return x < 0; }) << "\n";
  out << "Zero: " << std::count_if(v.begin(), v.end(), [](int x) { return x == 0; }) << "\n\n";

  double avg = (double)std::accumulate(v.begin(), v.end(), 0) / v.size();
  out << "Avg: " << avg << "\n\n";

  v.erase(std::remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), v.end());
  std::for_each(v.begin(), v.end(), [&](int x) { out << x << " "; });
  out << "\n\n";

  std::vector<int> uniqueV;
  std::unique_copy(v.begin(), v.end(), std::back_inserter(uniqueV));
  std::for_each(uniqueV.begin(), uniqueV.end(), [&](int x) { out << x << " "; });

  return 0;
}