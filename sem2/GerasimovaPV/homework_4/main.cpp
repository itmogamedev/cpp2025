#include <algorithm>
#include <fstream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

void writeVector(std::ofstream& out, const std::vector<int>& v) {
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(out, " "));
  out << "\n";
}

int main() {
  std::ofstream output_file("output.txt");

  // Генерация случайного вектора
  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution<int> distribution(-50, 100);
  std::vector<int> numbers(20);

  std::generate(numbers.begin(), numbers.end(),
                  [&]() { return distribution(generator); });
  output_file << "Initial vector:\n";
  writeVector(output_file, numbers);

  // min и max
  auto [min_it, max_it] = std::minmax_element(numbers.begin(), numbers.end());

  output_file << "\nMin element: " << *min_it
                << "\nMax element: " << *max_it << "\n";

  // сортировка
  std::vector<int> sorted_numbers = numbers;
  std::sort(sorted_numbers.begin(), sorted_numbers.end());

  output_file << "\nSorted vector:\n";
  writeVector(output_file, sorted_numbers);

  // подсчёт положительных, отрицательных и нулей
  auto positive_count = std::count_if(numbers.begin(), numbers.end(),
                                        [](int x) { return x > 0; });

  auto negative_count = std::count_if(numbers.begin(), numbers.end(),
                                        [](int x) { return x < 0; });
  auto zero_count = std::count(numbers.begin(), numbers.end(), 0);

  output_file << "\nPositive: " << positive_count
                << "\nNegative: " << negative_count
                << "\nZeros: " << zero_count << "\n";

  // среднее арифметическое
  double average = std::accumulate(numbers.begin(), numbers.end(), 0.0)
                     / numbers.size();

  output_file << "\nAverage: " << average << "\n";

  // удалить элементы меньше среднего
  std::vector<int> filtered_numbers = numbers;
  filtered_numbers.erase(
        std::remove_if(filtered_numbers.begin(), filtered_numbers.end(),
                       [average](int x) { return x < average; }),
        filtered_numbers.end());

  output_file << "\nFiltered vector (>= average):\n";
  writeVector(output_file, filtered_numbers);

  // сортировка + уникальные значения
  std::sort(filtered_numbers.begin(), filtered_numbers.end());

  std::vector<int> unique_numbers;
  std::unique_copy(filtered_numbers.begin(), filtered_numbers.end(),
                     std::back_inserter(unique_numbers));

  output_file << "\nUnique sorted vector:\n";
  writeVector(output_file, unique_numbers);

  return 0;
}