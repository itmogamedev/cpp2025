#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

int main() {
  std::ofstream output("output.txt");
  if (!output) {
    std::cerr << "Failed to create output.txt\n";
    return 1;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(-50, 100);

  std::vector<int> vec(20);
  std::generate(vec.begin(), vec.end(), [&gen, &dist]() { return dist(gen); });

  output << "Generated vector:\n";
  std::for_each(vec.begin(), vec.end(),
                [&output](int n) { output << n << " "; });
  output << "\n\n";

  auto [min_it, max_it] = std::minmax_element(vec.begin(), vec.end());
  output << "Min element: " << *min_it << "\n";
  output << "Max element: " << *max_it << "\n\n";

  std::sort(vec.begin(), vec.end());
  output << "Sorted vector:\n";
  std::for_each(vec.begin(), vec.end(),
                [&output](int n) { output << n << " "; });
  output << "\n\n";

  int positives =
      std::count_if(vec.begin(), vec.end(), [](int n) { return n > 0; });
  int negatives =
      std::count_if(vec.begin(), vec.end(), [](int n) { return n < 0; });
  int zeros =
      std::count_if(vec.begin(), vec.end(), [](int n) { return n == 0; });
  output << "Positive count: " << positives << "\n";
  output << "Negative count: " << negatives << "\n";
  output << "Zero count: " << zeros << "\n\n";

  double sum = 0.0;
  std::for_each(vec.begin(), vec.end(), [&sum](int n) { sum += n; });
  double average = sum / vec.size();
  output << "Average: " << average << "\n\n";

  vec.erase(
      std::remove_if(vec.begin(), vec.end(), [](int n) { return n % 2 == 0; }),
      vec.end());
  output << "After removing even numbers:\n";
  std::for_each(vec.begin(), vec.end(),
                [&output](int n) { output << n << " "; });
  output << "\n\n";

  std::sort(vec.begin(), vec.end());
  vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
  output << "Unique values:\n";
  std::for_each(vec.begin(), vec.end(),
                [&output](int n) { output << n << " "; });
  output << "\n";

  output.close();
  std::cout << "Done. Check output.txt\n";
  return 0;
}
