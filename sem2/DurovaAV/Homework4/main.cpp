#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

int main() {
  std::ofstream outFile("output.txt");
  if (!outFile.is_open()) {
    std::cerr << "Error: cannot create output.txt" << std::endl;
    return 1;
  }

  // генерация вектора
  std::vector<int> numbers(20);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::generate(numbers.begin(), numbers.end(),
                [&dist, &gen]() { return dist(gen); });

  outFile << "*+- Generated vector -+*\n";
  std::for_each(numbers.begin(), numbers.end(),
                [&outFile](int n) { outFile << n << " "; });
  outFile << "\n\n";

  // минимальный и максимальный элементы
  auto [minIt, maxIt] = std::minmax_element(numbers.begin(), numbers.end());
  outFile << "*+- Min and max elements -+*\n";
  outFile << "Min: " << *minIt << "\n";
  outFile << "Max: " << *maxIt << "\n\n";

  // сортировка
  std::sort(numbers.begin(), numbers.end());
  outFile << "*+- Sorted vector (ascending) -+*\n";
  std::for_each(numbers.begin(), numbers.end(),
                [&outFile](int n) { outFile << n << " "; });
  outFile << "\n\n";

  // подсчёт элементов
  int positiveCount = std::count_if(numbers.begin(), numbers.end(),
                                    [](int n) { return n > 0; });
  int negativeCount = std::count_if(numbers.begin(), numbers.end(),
                                    [](int n) { return n < 0; });
  int zeroCount = std::count_if(numbers.begin(), numbers.end(),
                                [](int n) { return n == 0; });

  outFile << "*+- Count of elements -+*\n";
  outFile << "Positive: " << positiveCount << "\n";
  outFile << "Negative: " << negativeCount << "\n";
  outFile << "Zero: " << zeroCount << "\n\n";

  // среднее арифметическое элементов
  double average =
      std::accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();
  outFile << "*+- Arithmetic mean -+*\n";
  outFile << average << "\n\n";

  // удаление чисел, которые меньше среднего арифметического
  std::vector<int> filtered = numbers;
  filtered.erase(std::remove_if(filtered.begin(), filtered.end(),
                                [average](int n) {
                                  return static_cast<double>(n) < average;
                                }),
                 filtered.end());

  outFile << "*+- After removing numbers less than average -+*\n";
  std::for_each(filtered.begin(), filtered.end(),
                [&outFile](int n) { outFile << n << " "; });
  outFile << "\n\n";

  // сортировка и создание вектора с уникальными значениями
  std::sort(filtered.begin(), filtered.end());
  auto last = std::unique(filtered.begin(), filtered.end());
  filtered.erase(last, filtered.end());

  outFile << "*+- Unique values (sorted) -+*\n";
  std::for_each(filtered.begin(), filtered.end(),
                [&outFile](int n) { outFile << n << " "; });
  outFile << "\n";

  outFile.close();

  std::cout << "Processing completed! Check output.txt" << std::endl;

  return 0;
}
