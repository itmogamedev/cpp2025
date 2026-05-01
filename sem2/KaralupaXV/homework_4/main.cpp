#include <algorithm>
#include <fstream>
#include <random>
#include <vector>

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(-50, 100);

  std::vector<int> array(20);
  std::generate(array.begin(), array.end(),
                [&distr, &gen]() { return distr(gen); });

  std::ofstream output_file("output.txt");

  output_file << "min: " << *std::min_element(array.begin(), array.end())
              << "\n";
  output_file << "max: " << *std::max_element(array.begin(), array.end())
              << "\n";

  output_file << "sorted array: ";
  std::sort(array.begin(), array.end());
  std::for_each(array.begin(), array.end(),
                [&output_file](int item) { output_file << item << " "; });
  output_file << "\n";

  auto left = std::lower_bound(array.begin(), array.end(), 0);
  auto right = std::upper_bound(array.begin(), array.end(), 0);

  int negative = left - array.begin();
  int positive = array.end() - right;
  int nulls = right - left;

  output_file << "numbers<0: " << negative << "\n";
  output_file << "numbers=0: " << nulls << "\n";
  output_file << "numbers>0: " << positive << "\n";

  int sum = std::accumulate(array.begin(), array.end(), 0);
  float avg = static_cast<float>(sum) / array.size();

  output_file << "average: " << avg << "\n";

  auto filtered_start = std::lower_bound(array.begin(), array.end(), avg);
  std::vector<int> new_array(filtered_start, array.end());

  output_file << "filtered array: ";
  std::sort(new_array.begin(), new_array.end());
  std::for_each(new_array.begin(), new_array.end(),
                [&output_file](int item) { output_file << item << " "; });
  output_file << "\n";

  auto unique_end = std::unique(new_array.begin(), new_array.end());
  new_array.erase(unique_end, new_array.end());

  output_file << "unique array: ";
  std::sort(new_array.begin(), new_array.end());
  std::for_each(new_array.begin(), new_array.end(),
                [&output_file](int item) { output_file << item << " "; });
  output_file << "\n";

  output_file << std::endl;

  output_file.close();

  return 0;
}