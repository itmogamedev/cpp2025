#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

int main() {
  setlocale(LC_ALL, "Russian");
  // открываем файл для записи результатов
  std::ofstream outputFile("output.txt");
  if (!outputFile.is_open()) {
    std::cerr << "Ошибка открытия файла output.txt" << std::endl;
    return 1;
  }

  // генерируем вектор из 20 целых чисел в диапазоне
  std::vector<int> numbers(20);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(-50, 100);

  std::generate(numbers.begin(), numbers.end(),
                [&dist, &gen]() { return dist(gen); });

  // выводим исходный вектор
  outputFile << "Исходный вектор: ";
  std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<int>(outputFile, " "));
  outputFile << "\n\n";

  // находим минимальный и максимальный элементы
  auto [minIt, maxIt] = std::minmax_element(numbers.begin(), numbers.end());
  outputFile << "Минимальный элемент: " << *minIt << std::endl;
  outputFile << "Максимальный элемент: " << *maxIt << "\n\n";

  // сортируем вектор по возрастанию
  std::sort(numbers.begin(), numbers.end());
  outputFile << "Отсортированный вектор по возрастанию: ";
  std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<int>(outputFile, " "));
  outputFile << "\n\n";

  // подсчитываем количество положительных, отрицательных и нулевых элементов
  int positiveCount = std::count_if(numbers.begin(), numbers.end(),
                                    [](int x) { return x > 0; });
  int negativeCount = std::count_if(numbers.begin(), numbers.end(),
                                    [](int x) { return x < 0; });
  int zeroCount = std::count_if(numbers.begin(), numbers.end(),
                                [](int x) { return x == 0; });

  outputFile << "Количество положительных элементов: " << positiveCount
             << std::endl;
  outputFile << "Количество отрицательных элементов: " << negativeCount
             << std::endl;
  outputFile << "Количество нулевых элементов: " << zeroCount << "\n\n";

  // находим среднее арифметическое всех элементов
  int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
  double average = static_cast<double>(sum) / numbers.size();
  outputFile << "Среднее арифметическое всех элементов: " << average << "\n\n";

  // удаляем из вектора все чётные числа
  numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                               [](int x) { return x % 2 == 0; }),
                numbers.end());

  outputFile << "Вектор после удаления чётных чисел: ";
  std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<int>(outputFile, " "));
  outputFile << "\n\n";

  // сортируем полученный вектор
  std::sort(numbers.begin(), numbers.end());
  outputFile << "Вектор после удаления чётных чисел, отсортированный: ";
  std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<int>(outputFile, " "));
  outputFile << "\n\n";

  // создаём новый вектор с уникальными значениями
  std::vector<int> uniqueNumbers;
  std::unique_copy(numbers.begin(), numbers.end(),
                   std::back_inserter(uniqueNumbers));

  outputFile << "Вектор с уникальными значениями: ";
  std::copy(uniqueNumbers.begin(), uniqueNumbers.end(),
            std::ostream_iterator<int>(outputFile, " "));
  outputFile << std::endl;

  outputFile.close();

  std::cout << "Результаты записаны в файл output.txt" << std::endl;

  return 0;
}
