#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <string>
#include <vector>

std::vector<int> generateNumbers() {
  std::vector<int> numbers(20);

  std::random_device randomDevice;
  std::mt19937 generator(randomDevice());
  std::uniform_int_distribution<int> distribution(-50, 100);

  std::generate(numbers.begin(), numbers.end(), [&generator, &distribution]() {
    return distribution(generator);
  });

  return numbers;
}

void writeVector(std::ofstream& output, const std::string& title,
                 const std::vector<int>& numbers) {
  output << title << "\n";

  std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<int>(output, " "));

  output << "\n\n";
}

void writeMinMax(std::ofstream& output, const std::vector<int>& numbers) {
  auto minMax = std::minmax_element(numbers.begin(), numbers.end());

  output << "Минимальный элемент: " << *minMax.first << "\n";
  output << "Максимальный элемент: " << *minMax.second << "\n\n";
}

std::vector<int> getSortedVector(std::vector<int> numbers) {
  std::sort(numbers.begin(), numbers.end());
  return numbers;
}

void writeCounts(std::ofstream& output, const std::vector<int>& numbers) {
  int positiveCount = static_cast<int>(std::count_if(
      numbers.begin(), numbers.end(), [](int number) { return number > 0; }));

  int negativeCount = static_cast<int>(std::count_if(
      numbers.begin(), numbers.end(), [](int number) { return number < 0; }));

  int zeroCount =
      static_cast<int>(std::count(numbers.begin(), numbers.end(), 0));

  output << "Количество положительных элементов: " << positiveCount << "\n";
  output << "Количество отрицательных элементов: " << negativeCount << "\n";
  output << "Количество нулевых элементов: " << zeroCount << "\n\n";
}

double getAverage(const std::vector<int>& numbers) {
  int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
  return static_cast<double>(sum) / numbers.size();
}

std::vector<int> removeLessThanAverage(const std::vector<int>& numbers,
                                       double average) {
  std::vector<int> result = numbers;

  result.erase(
      std::remove_if(result.begin(), result.end(),
                     [average](int number) { return number < average; }),
      result.end());

  return result;
}

std::vector<int> getSortedUniqueVector(std::vector<int> numbers) {
  std::sort(numbers.begin(), numbers.end());

  auto last = std::unique(numbers.begin(), numbers.end());
  numbers.erase(last, numbers.end());

  return numbers;
}

void solve() {
  std::vector<int> numbers = generateNumbers();
  std::ofstream output("output.txt");

  writeVector(output, "Исходный вектор:", numbers);
  writeMinMax(output, numbers);

  std::vector<int> sortedNumbers = getSortedVector(numbers);
  writeVector(output, "Отсортированный вектор:", sortedNumbers);

  writeCounts(output, numbers);

  double average = getAverage(numbers);
  output << "Среднее арифметическое: " << average << "\n\n";

  std::vector<int> filteredNumbers = removeLessThanAverage(numbers, average);
  writeVector(output,
              "Вектор после удаления чисел меньше среднего:", filteredNumbers);

  std::vector<int> uniqueNumbers = getSortedUniqueVector(filteredNumbers);
  writeVector(output,
              "Отсортированный вектор уникальных значений:", uniqueNumbers);
}

int main() {
  solve();
  return 0;
}
