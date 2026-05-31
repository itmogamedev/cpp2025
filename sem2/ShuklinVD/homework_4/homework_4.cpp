#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

void writeVector(std::ofstream& fout, const std::vector<int>& v) {
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(fout, " "));
  fout << "\n";
}

void run() {
  std::ofstream fout("output.txt");

  std::vector<int> v(20);
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> dist(-50, 100);
  std::generate(v.begin(), v.end(), [&gen, &dist]() { return dist(gen); });

  fout << "=== Исходный вектор ===\n";
  writeVector(fout, v);

  auto minmax = std::minmax_element(v.begin(), v.end());
  fout << "\n=== Минимум и максимум ===\n";
  fout << "Минимум: " << *minmax.first << "\n";
  fout << "Максимум: " << *minmax.second << "\n";

  std::sort(v.begin(), v.end());
  fout << "\n=== Отсортированный вектор ===\n";
  writeVector(fout, v);

  int positive = std::count_if(v.begin(), v.end(), [](int x) { return x > 0; });
  int negative = std::count_if(v.begin(), v.end(), [](int x) { return x < 0; });
  int zeros = std::count_if(v.begin(), v.end(), [](int x) { return x == 0; });
  fout << "\n=== Количество элементов ===\n";
  fout << "Положительных: " << positive << "\n";
  fout << "Отрицательных: " << negative << "\n";
  fout << "Нулей: " << zeros << "\n";

  float sum = std::accumulate(v.begin(), v.end(), 0);
  float average = sum / v.size();
  fout << "\n=== Среднее арифметическое ===\n";
  fout << average << "\n";

  v.erase(std::remove_if(v.begin(), v.end(),
                         [average](int x) { return x < average; }),
          v.end());
  fout << "\n=== Вектор после удаления чисел меньше среднего ===\n";
  writeVector(fout, v);

  std::vector<int> unique_v;
  std::unique_copy(v.begin(), v.end(), std::back_inserter(unique_v));
  fout << "\n=== Уникальные значения ===\n";
  writeVector(fout, unique_v);

  fout.close();
}

int main() {
  setlocale(LC_ALL, "");
  run();
}
