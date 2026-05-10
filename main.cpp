#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <string>
#include <vector>

// функция для вывода вектора без циклов
void printVector(std::ofstream& out, const std::vector<int>& vec,
                 const std::string& title) {
  out << "--- " << title << " ---\n";
  // алгоритм std::copy для вывода элементов
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << "\n\n";
}

int main() {
  std::ofstream out_file("output.txt");
  if (!out_file.is_open()) {
    std::cerr << "Failed to open output.txt\n";
    return 1;
  }

  // генерация 20 чисел
  std::vector<int> numbers(20);
  std::random_device rd;
  std::mt19937 random_gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::generate(numbers.begin(), numbers.end(),
                [&random_gen, &dist]() { return dist(random_gen); });

  printVector(out_file, numbers, "1. Initial generated vector");

  // минимальный и максимальный элементы
  auto min_max = std::minmax_element(numbers.begin(), numbers.end());
  out_file << "--- 2. Min and Max elements ---\n";
  out_file << "Min: " << *min_max.first << "\n";
  out_file << "Max: " << *min_max.second << "\n\n";

  // сортировка
  std::sort(numbers.begin(), numbers.end());
  printVector(out_file, numbers, "3. Sorted vector");

  // количество положительных, отрицательных и нулевых элементов
  int positive_count = std::count_if(numbers.begin(), numbers.end(),
                                     [](int val) { return val > 0; });
  int negative_count = std::count_if(numbers.begin(), numbers.end(),
                                     [](int val) { return val < 0; });
  int zero_count = std::count_if(numbers.begin(), numbers.end(),
                                 [](int val) { return val == 0; });

  out_file << "--- 4. Element counts ---\n";
  out_file << "Positive: " << positive_count << "\n";
  out_file << "Negative: " << negative_count << "\n";
  out_file << "Zeros: " << zero_count << "\n\n";

  // среднее арифметическое всех элементов
  double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
  double mean = sum / numbers.size();

  out_file << "--- 5. Arithmetic mean ---\n";
  out_file << "Mean: " << mean << "\n\n";

  // удаление чисел
  numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                               [](int val) { return val % 2 == 0; }),
                numbers.end());

  printVector(out_file, numbers, "6. Vector after removing even numbers");

  // новый вектор с уникальными значениями
  std::sort(numbers.begin(), numbers.end());

  std::vector<int> unique_numbers;
  std::unique_copy(numbers.begin(), numbers.end(),
                   std::back_inserter(unique_numbers));

  printVector(out_file, unique_numbers, "7. New vector with unique values");

  out_file.close();
  std::cout << "Processing complete. Check output.txt file.\n";

  return 0;
}