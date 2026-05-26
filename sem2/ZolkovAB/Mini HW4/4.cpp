#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

void writeVector(std::ofstream& ofs, const std::vector<int>& vec,
                 const std::string& label) {
  ofs << label << ": ";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(ofs, " "));
  ofs << "\n";
}

int main() {
  std::ofstream outfile("output.txt");
  std::vector<int> data(20);

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> dist(-50, 100);
  std::generate(data.begin(), data.end(), [&]() { return dist(gen); });
  writeVector(outfile, data, "Generated Vector");

  auto [min_it, max_it] = std::minmax_element(data.begin(), data.end());
  outfile << "Min: " << *min_it << ", Max: " << *max_it << "\n";

  std::sort(data.begin(), data.end());
  writeVector(outfile, data, "Sorted Vector");

  long pos =
      std::count_if(data.begin(), data.end(), [](int n) { return n > 0; });
  long neg =
      std::count_if(data.begin(), data.end(), [](int n) { return n < 0; });
  long zero =
      std::count_if(data.begin(), data.end(), [](int n) { return n == 0; });
  outfile << "Positive: " << pos << ", Negative: " << neg << ", Zeros: " << zero
          << "\n";

  double sum = std::accumulate(data.begin(), data.end(), 0.0);
  double mean = sum / data.size();
  outfile << "Mean: " << mean << "\n";

  auto new_end = std::remove_if(data.begin(), data.end(),
                                [mean](int n) { return n < mean; });
  data.erase(new_end, data.end());
  writeVector(outfile, data, "After Variant 2 Processing (Removed < Mean)");

  std::sort(data.begin(), data.end());
  auto last_unique = std::unique(data.begin(), data.end());
  std::vector<int> unique_data(data.begin(), last_unique);
  writeVector(outfile, unique_data, "Unique Elements");

  outfile.close();
  return 0;
}