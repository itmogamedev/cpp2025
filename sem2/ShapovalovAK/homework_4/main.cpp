#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <string>
#include <vector>

int main() {
  std::ofstream fileOut("output.txt");

  // 1. Генерация вектора
  std::vector<int> numbers(20);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::generate(numbers.begin(), numbers.end(), [&]() { return dist(gen); });
  fileOut << "Исходный вектор:" << std::endl;

  std::for_each(numbers.begin(), numbers.end(),
                [&fileOut](int value) { fileOut << value << " "; });

  fileOut << std::endl << std::endl;

  // 2. Минимальный и максимальный элементы
  auto minMax = std::minmax_element(numbers.begin(), numbers.end());

  fileOut << "Минимальный элемент: " << *minMax.first << std::endl;
  fileOut << "Максимальный элемент: " << *minMax.second << std::endl
          << std::endl;

  // 3. Сортировка по возрастанию
  std::sort(numbers.begin(), numbers.end());

  fileOut << "Отсортированный вектор:" << std::endl;

  std::for_each(numbers.begin(), numbers.end(),
                [&fileOut](int value) { fileOut << value << " "; });

  fileOut << std::endl << std::endl;

  // 4. Подсчет положительных, отрицательных и нулевых элементов
  int positiveCount = std::count_if(numbers.begin(), numbers.end(),
                                    [](int value) { return value > 0; });

  int negativeCount = std::count_if(numbers.begin(), numbers.end(),
                                    [](int value) { return value < 0; });

  int zeroCount = std::count(numbers.begin(), numbers.end(), 0);

  fileOut << "Количество положительных: " << positiveCount << std::endl;
  fileOut << "Количество отрицательных: " << negativeCount << std::endl;
  fileOut << "Количество нулевых: " << zeroCount << std::endl << std::endl;

  // 5. Среднее арифметическое
  double average =
      static_cast<double>(std::accumulate(numbers.begin(), numbers.end(), 0)) /
      numbers.size();

  fileOut << "Среднее арифметическое: " << average << std::endl << std::endl;

  // 6. Удаление элементов меньше среднего
  numbers.erase(
      std::remove_if(numbers.begin(), numbers.end(),
                     [average](int value) { return value < average; }),
      numbers.end());

  fileOut << "Вектор после удаления элементов меньше среднего:" << std::endl;

  std::for_each(numbers.begin(), numbers.end(),
                [&fileOut](int value) { fileOut << value << " "; });

  fileOut << std::endl << std::endl;

  // 7. Создание вектора с уникальными значениями
  std::sort(numbers.begin(), numbers.end());

  std::set<int> uniqueSet(numbers.begin(), numbers.end());

  std::vector<int> uniqueNumbers(uniqueSet.begin(), uniqueSet.end());

  fileOut << "Вектор с уникальными значениями:" << std::endl;

  std::for_each(uniqueNumbers.begin(), uniqueNumbers.end(),
                [&fileOut](int value) { fileOut << value << " "; });

  fileOut << std::endl;

  fileOut.close();

  return 0;
}
