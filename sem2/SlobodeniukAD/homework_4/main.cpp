#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

// Функция для вывода вектора в файл
void writeVector(std::ofstream& outFile, const std::vector<int>& vec) {
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(outFile, " "));
  outFile << "\n";
}

void runTask(std::ofstream& outFile) {
  // 1. Генерация случайного вектора от -50 до 100
  std::vector<int> numbers(20);
  std::mt19937 generator(std::random_device{}());
  std::uniform_int_distribution<int> distribution(-50, 100);
  std::generate(numbers.begin(), numbers.end(), [&generator, &distribution]() {
    return distribution(generator);
  });
  outFile << "Generated vector: ";
  writeVector(outFile, numbers);

  // 2. Поиск минимального и максимального элементов
  auto minMaxPair = std::minmax_element(numbers.begin(), numbers.end());
  outFile << "Min element: " << *(minMaxPair.first) << "\n";
  outFile << "Max element: " << *(minMaxPair.second) << "\n";

  // 3. Сортировка по возрастанию
  std::sort(numbers.begin(), numbers.end());
  outFile << "Sorted vector: ";
  writeVector(outFile, numbers);

  // 4. Подсчет количества положительных, отрицательных и нулевых элементов
  long long positiveCount = std::count_if(numbers.begin(), numbers.end(),
                                          [](int val) { return val > 0; });
  long long negativeCount = std::count_if(numbers.begin(), numbers.end(),
                                          [](int val) { return val < 0; });
  long long zeroCount = std::count_if(numbers.begin(), numbers.end(),
                                      [](int val) { return val == 0; });
  outFile << "Positive: " << positiveCount << ", Negative: " << negativeCount
          << ", Zero: " << zeroCount << "\n";

  // 5. Среднее арифметическое
  double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
  double average = sum / numbers.size();
  outFile << "Average: " << average << "\n";

  // 6. Удаление элементов, которые меньше среднего арифметического
  auto removeIt = std::remove_if(numbers.begin(), numbers.end(),
                                 [average](int val) { return val < average; });
  numbers.erase(removeIt, numbers.end());
  outFile << "Vector after removing elements less than average: ";
  writeVector(outFile, numbers);

  // 7. Сортировка полученного вектора и создание нового с уникальными
  // значениями
  std::sort(numbers.begin(), numbers.end());
  std::vector<int> uniqueNumbers;
  std::unique_copy(numbers.begin(), numbers.end(),
                   std::back_inserter(uniqueNumbers));
  outFile << "Unique elements vector: ";
  writeVector(outFile, uniqueNumbers);
}

int main() {
  std::ofstream outFile("output.txt");
  if (!outFile.is_open()) {
    return 1;
  }
  runTask(outFile);
  outFile.close();
  return 0;
}
