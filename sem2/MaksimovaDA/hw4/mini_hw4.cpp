#include <Windows.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::vector<int> numbers(20);
  std::generate(numbers.begin(), numbers.end(), [&]() { return dist(rng); });

  std::ofstream output_file("output.txt");
  if (!output_file.is_open()) {
    std::cout << "no output.txt" << std::endl;
    return 1;
  }

  auto printVector = [&output_file](const std::vector<int>& vec,
                                    const std::string& title) {
    output_file << title << std::endl;
    for (int val : vec) {
      output_file << val << " ";
    }
    output_file << std::endl << std::endl;
  };

  printVector(numbers, "1. vector: ");

  auto [min_it, max_it] = std::minmax_element(numbers.begin(), numbers.end());
  output_file << "2. min: " << *min_it << std::endl;
  output_file << "max: " << *max_it << std::endl << std::endl;

  std::vector<int> sorted_numbers = numbers;
  std::sort(sorted_numbers.begin(), sorted_numbers.end());
  printVector(sorted_numbers, "3. sorted:");

  int positive_count = std::count_if(numbers.begin(), numbers.end(),
                                     [](int x) { return x > 0; });
  int negative_count = std::count_if(numbers.begin(), numbers.end(),
                                     [](int x) { return x < 0; });
  int zero_count = std::count_if(numbers.begin(), numbers.end(),
                                 [](int x) { return x == 0; });

  output_file << "4. count of positive elements: " << positive_count
              << std::endl;
  output_file << "count of negative elements: " << negative_count
              << std::endl;
  output_file << "count of zero elements: " << zero_count << std::endl
              << std::endl;

  double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
  double average = sum / numbers.size();
  output_file << "5. average: " << average << std::endl
              << std::endl;

  std::vector<int> odd_sorted = sorted_numbers;
  odd_sorted.erase(std::remove_if(odd_sorted.begin(), odd_sorted.end(),
                                  [](int x) { return x % 2 == 0; }),
                   odd_sorted.end());
  printVector(odd_sorted, "6. without even:");

  std::vector<int> unique_numbers = odd_sorted;
  unique_numbers.erase(
      std::unique(unique_numbers.begin(), unique_numbers.end()),
      unique_numbers.end());
  printVector(unique_numbers, "7. sorted unique:");

  output_file.close();

  return 0;
}