#include "vector_processor.h"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <numeric>

void process_and_write_results(const std::vector<int>& original_vec,
                               const std::string& filename) {
  std::ofstream out(filename);

  auto vec = original_vec;

  auto [min_it, max_it] = std::minmax_element(vec.begin(), vec.end());
  out << "Minimum element: " << *min_it << "\n";
  out << "Maximum element: " << *max_it << "\n\n";

  std::sort(vec.begin(), vec.end());
  out << "Sorted vector: ";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << "\n\n";

  auto positive_count =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x > 0; });
  auto negative_count =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x < 0; });
  auto zero_count =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x == 0; });

  out << "Positive elements: " << positive_count << "\n";
  out << "Negative elements: " << negative_count << "\n";
  out << "Zero elements: " << zero_count << "\n\n";

  double average = std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
  out << "Arithmetic mean: " << average << "\n\n";

  vec.erase(
      std::remove_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; }),
      vec.end());
  out << "Vector after removing even numbers: ";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << "\n\n";

  std::sort(vec.begin(), vec.end());
  auto last = std::unique(vec.begin(), vec.end());
  std::vector<int> unique_vec(vec.begin(), last);

  out << "Unique sorted vector: ";
  std::copy(unique_vec.begin(), unique_vec.end(),
            std::ostream_iterator<int>(out, " "));
  out << "\n";

  out.close();
}
