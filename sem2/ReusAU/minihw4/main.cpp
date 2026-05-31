#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

void writeVector(std::ostream& out, const std::vector<int>& v) {
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(out, " "));
  out << "\n";
}

int main() {
  // Шаг 1: Генерация вектора из 20 чисел в диапазоне [-50, 100]
  std::vector<int> v(20);
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(-50, 100);
  std::generate(v.begin(), v.end(), [&rng, &dist]() { return dist(rng); });

  std::ofstream out("output.txt");

  // Шаг 2: Минимум и максимум
  auto min_it = std::min_element(v.begin(), v.end());
  auto max_it = std::max_element(v.begin(), v.end());
  out << "=== Минимум и максимум ===\n";
  out << "Минимум: " << *min_it << "\n";
  out << "Максимум: " << *max_it << "\n";

  // Шаг 3: Сортировка по возрастанию
  std::vector<int> sorted_v = v;
  std::sort(sorted_v.begin(), sorted_v.end());
  out << "\n=== Отсортированный вектор ===\n";
  writeVector(out, sorted_v);

  // Шаг 4: Подсчёт положительных, отрицательных и нулевых
  int positive = static_cast<int>(
      std::count_if(v.begin(), v.end(), [](int x) { return x > 0; }));
  int negative = static_cast<int>(
      std::count_if(v.begin(), v.end(), [](int x) { return x < 0; }));
  int zero = static_cast<int>(
      std::count_if(v.begin(), v.end(), [](int x) { return x == 0; }));
  out << "\n=== Количество элементов ===\n";
  out << "Положительных: " << positive << "\n";
  out << "Отрицательных: " << negative << "\n";
  out << "Нулевых: " << zero << "\n";

  // Шаг 5: Среднее арифметическое
  double mean = static_cast<double>(std::accumulate(v.begin(), v.end(), 0)) /
                static_cast<double>(v.size());
  out << "\n=== Среднее арифметическое ===\n";
  out << mean << "\n";

  // Шаг 6 (Вариант 1): Удаление чётных чисел
  std::vector<int> odd_v = v;
  odd_v.erase(std::remove_if(odd_v.begin(), odd_v.end(),
                             [](int x) { return x % 2 == 0; }),
              odd_v.end());
  out << "\n=== После удаления чётных чисел ===\n";
  writeVector(out, odd_v);

  // Шаг 7: Сортировка и уникальные значения
  std::sort(odd_v.begin(), odd_v.end());
  std::vector<int> unique_v;
  std::unique_copy(odd_v.begin(), odd_v.end(), std::back_inserter(unique_v));
  out << "\n=== Уникальные значения (отсортированные) ===\n";
  writeVector(out, unique_v);

  std::cout << "Results written to output.txt\n";
  return 0;
}
