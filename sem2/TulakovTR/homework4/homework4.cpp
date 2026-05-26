#include <windows.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

int main() {
  SetConsoleOutputCP(1251);
  SetConsoleCP(1251);
  std::ofstream outputFile("output.txt");

  // 1. Генерация вектора из 20 случайных чисел от -50 до 100
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::vector<int> vec(20);
  std::generate(vec.begin(), vec.end(), [&]() { return dist(rng); });

  outputFile << "1. Исходный вектор:\n";
  std::copy(vec.begin(), vec.end(),
            std::ostream_iterator<int>(outputFile, " "));
  outputFile << "\n\n";

  // 2. Минимальный и максимальный элементы
  auto [minIt, maxIt] = std::minmax_element(vec.begin(), vec.end());
  outputFile << "2. Минимальный и максимальный элементы:\n";
  outputFile << "   Минимум: " << *minIt << "\n";
  outputFile << "   Максимум: " << *maxIt << "\n\n";

  // 3. Сортировка по возрастанию
  std::sort(vec.begin(), vec.end());
  outputFile << "3. Отсортированный вектор:\n";
  std::copy(vec.begin(), vec.end(),
            std::ostream_iterator<int>(outputFile, " "));
  outputFile << "\n\n";

  // 4. Подсчёт положительных, отрицательных и нулевых элементов
  int positive =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x > 0; });
  int negative =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x < 0; });
  int zero =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x == 0; });

  outputFile << "4. Количество элементов:\n";
  outputFile << "   Положительных: " << positive << "\n";
  outputFile << "   Отрицательных: " << negative << "\n";
  outputFile << "   Нулевых: " << zero << "\n\n";

  // 5. Среднее арифметическое
  double average = std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
  outputFile << "5. Среднее арифметическое: " << average << "\n\n";

  // 6. Вариант 2: Удаление чисел меньше среднего арифметического
  std::vector<int> filtered = vec;
  filtered.erase(std::remove_if(filtered.begin(), filtered.end(),
                                [average](int x) { return x < average; }),
                 filtered.end());

  outputFile << "6. Вектор после удаления чисел меньше среднего:\n";
  std::copy(filtered.begin(), filtered.end(),
            std::ostream_iterator<int>(outputFile, " "));
  outputFile << "\n\n";

  // 7. Сортировка и уникальные значения
  std::sort(filtered.begin(), filtered.end());
  auto last = std::unique(filtered.begin(), filtered.end());
  std::vector<int> uniqueVec(filtered.begin(), last);

  outputFile << "7. Вектор с уникальными значениями:\n";
  std::copy(uniqueVec.begin(), uniqueVec.end(),
            std::ostream_iterator<int>(outputFile, " "));
  outputFile << "\n";

  outputFile.close();
  std::cout << "Готово! Результаты в output.txt\n";
  system("pause");
  return 0;
}