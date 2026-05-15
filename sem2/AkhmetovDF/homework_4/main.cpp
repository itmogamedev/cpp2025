#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

int main() {
  // генерация вектора из 20 целых чисел в диапазоне
  std::vector<int> v(20);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);
  std::generate(v.begin(), v.end(), [&]() { return dist(gen); });

  std::ofstream out("output.txt");
  if (!out) {
    std::cerr << "не удалось открыть файл output.txt\n";
    return 1;
  }

  // 2. поиск минимального и максимального элементов
  auto min_it = std::min_element(v.begin(), v.end());
  auto max_it = std::max_element(v.begin(), v.end());
  out << "min and max: " << *min_it << " " << *max_it << "\n\n";

  // 3. сортировка по возрастанию и вывод
  std::sort(v.begin(), v.end());
  out << "sorted vector:\n";
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(out, " "));
  out << "\n\n";

  // 4. подсчёт положительных, отрицательных и нулевых элементов
  int positive = std::count_if(v.begin(), v.end(), [](int x) { return x > 0; });
  int negative = std::count_if(v.begin(), v.end(), [](int x) { return x < 0; });
  int zero = std::count_if(v.begin(), v.end(), [](int x) { return x == 0; });
  out << "positive: " << positive << ", negative: " << negative
      << ", zero: " << zero << "\n\n";

  // 5. среднее арифметическое
  double average = std::accumulate(v.begin(), v.end(), 0.0) / v.size();
  out << "average: " << average << "\n\n";

  // 6. удаление всех чётных чисел
  v.erase(std::remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }),
          v.end());
  out << "vector after removing evens:\n";
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(out, " "));
  out << "\n\n";

  // 7. сортировка и создание вектора с уникальными значениями
  std::sort(v.begin(), v.end());
  auto last = std::unique(v.begin(), v.end());
  std::vector<int> uniqueV(v.begin(), last);
  out << "unique values:\n";
  std::copy(uniqueV.begin(), uniqueV.end(),
            std::ostream_iterator<int>(out, " "));
  out << "\n";

  return 0;
}
