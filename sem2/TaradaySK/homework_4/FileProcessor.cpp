#include "FileProcessor.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

void runRandomProcessing() {
  std::string line = "*******************************************************";
  std::ofstream output("output.txt");
  if (!output.is_open()) return;
  std::vector<int> numbers(20);
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dist(-50, 100);
  std::generate(numbers.begin(), numbers.end(), [&]() { return dist(gen); });
  output << line << "\nИсходный вектор\n";
  std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<int>(output, " "));
  auto itMin = std::min_element(numbers.begin(), numbers.end());
  auto itMax = std::max_element(numbers.begin(), numbers.end());
  output << "\n" << line << "\nMin: " << *itMin << ", Max: " << *itMax << "\n";
  std::sort(numbers.begin(), numbers.end());
  output << line << "\nОтсортированный вектор\n";
  std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<int>(output, " "));
  long long pos = std::count_if(numbers.begin(), numbers.end(),
                                [](int n) { return n > 0; });
  long long neg = std::count_if(numbers.begin(), numbers.end(),
                                [](int n) { return n < 0; });
  long long zero = std::count_if(numbers.begin(), numbers.end(),
                                 [](int n) { return n == 0; });
  output << "\n"
         << line << "\nПоложительных: " << pos << ", Отрицательных: " << neg
         << ", Нулей: " << zero << "\n";
  double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
  output << line << "\nСреднее: " << sum / numbers.size() << "\n";
  numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                               [](int n) { return n % 2 == 0; }),
                numbers.end());
  output << line << "\nБез чётных\n";
  std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<int>(output, " "));
  std::sort(numbers.begin(), numbers.end());
  std::vector<int> unique_vec;
  std::unique_copy(numbers.begin(), numbers.end(),
                   std::back_inserter(unique_vec));
  output << "\n" << line << "\nУникальные\n";
  std::copy(unique_vec.begin(), unique_vec.end(),
            std::ostream_iterator<int>(output, " "));
  output << "\n" << line;
  output.close();
}
