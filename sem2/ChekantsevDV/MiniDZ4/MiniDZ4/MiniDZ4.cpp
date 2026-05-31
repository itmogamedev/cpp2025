#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

int main() {
  setlocale(LC_ALL, "rus");
  std::ofstream out_file("output.txt");

  std::vector<int> numbers(20);
  std::mt19937 generator(std::random_device{}());
  std::uniform_int_distribution<int> distribution(-50, 100);
  std::generate(numbers.begin(), numbers.end(),
                [&]() { return distribution(generator); });

  auto [min_iter, max_iter] =
      std::minmax_element(numbers.begin(), numbers.end());
  out_file << "Минимальный элемент: " << *min_iter << "\n";
  out_file << "Максимальный элемент: " << *max_iter << "\n\n";

  std::sort(numbers.begin(), numbers.end());
  out_file << "Отсортированный вектор: ";
  std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<int>(out_file, " "));
  out_file << "\n\n";

  int positive_count = std::count_if(numbers.begin(), numbers.end(),
                                     [](int x) { return x > 0; });
  int negative_count = std::count_if(numbers.begin(), numbers.end(),
                                     [](int x) { return x < 0; });
  int zero_count = std::count_if(numbers.begin(), numbers.end(),
                                 [](int x) { return x == 0; });
  out_file << "Положительных: " << positive_count << "\n";
  out_file << "Отрицательных: " << negative_count << "\n";
  out_file << "Нулевых: " << zero_count << "\n\n";

  double mean =
      std::accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();
  out_file << "Среднее арифметическое: " << mean << "\n\n";

  numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                               [mean](int x) { return x < mean; }),
                numbers.end());
  out_file << "Вектор после удаления элементов < среднего: ";
  std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<int>(out_file, " "));
  out_file << "\n\n";

  std::sort(numbers.begin(), numbers.end());
  std::vector<int> unique_values;
  std::unique_copy(numbers.begin(), numbers.end(),
                   std::back_inserter(unique_values));
  out_file << "Вектор с уникальными значениями: ";
  std::copy(unique_values.begin(), unique_values.end(),
            std::ostream_iterator<int>(out_file, " "));
  out_file << "\n";
}
