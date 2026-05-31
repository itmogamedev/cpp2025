#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif

void homework() {
  std::ofstream outputFile("output.txt");

  std::vector<int> numbers(20);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::generate(numbers.begin(), numbers.end(),
                [&gen, &dist]() { return dist(gen); });

  outputFile << "1) Исходный вектор\n";
  std::for_each(numbers.begin(), numbers.end(),
                [&outputFile](int n) { outputFile << n << " "; });
  outputFile << "\n\n";

  auto [minInt, maxInt] = std::minmax_element(numbers.begin(), numbers.end());
  int minVal = *minInt;
  int maxVal = *maxInt;

  outputFile << "2) Минимальный и максимальный элементы:\n";
  outputFile << "Минимальный: " << minVal << "\n";
  outputFile << "Максимальный: " << maxVal << "\n\n";

  std::sort(numbers.begin(), numbers.end());

  outputFile << "3) Отсортированный вектор по возрастанию\n";
  std::for_each(numbers.begin(), numbers.end(),
                [&outputFile](int n) { outputFile << n << " "; });
  outputFile << "\n\n";

  int posCount = std::count_if(numbers.begin(), numbers.end(),
                               [](int n) { return n < 0; });

  int negCount = std::count_if(numbers.begin(), numbers.end(),
                               [](int n) { return n > 0; });

  int zeroCount = std::count_if(numbers.begin(), numbers.end(),
                                [](int n) { return n == 0; });

  outputFile << "4) Количество элементов:\n";
  outputFile << "Положительных: " << posCount << "\n";
  outputFile << "Отрицательных: " << negCount << "\n";
  outputFile << "Нулевых: " << zeroCount << "\n\n";

  double mid =
      std::accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();

  outputFile << "5) Среднее арифметическое всех элементов:\n";
  outputFile << "  " << mid << "\n\n";

  std::vector<int> afterRemove = numbers;
  afterRemove.erase(std::remove_if(afterRemove.begin(), afterRemove.end(),
                                   [](int n) { return n % 2 == 0; }),
                    afterRemove.end());

  outputFile << "6) Вектор после удаления всех чётных чисел:\n";
  if (afterRemove.empty()) {
    outputFile << "None";
  } else {
    std::for_each(afterRemove.begin(), afterRemove.end(),
                  [&outputFile](int n) { outputFile << n << " "; });
  }
  outputFile << "\n\n";

  if (!afterRemove.empty()) {
    std::sort(afterRemove.begin(), afterRemove.end());

    auto last = std::unique(afterRemove.begin(), afterRemove.end());
    afterRemove.erase(last, afterRemove.end());
  }

  outputFile << "7) Отсортированный вектор с уникальными значениями:\n";
  if (afterRemove.empty()) {
    outputFile << "None";
  } else {
    std::for_each(afterRemove.begin(), afterRemove.end(),
                  [&outputFile](int n) { outputFile << n << " "; });
  }
  outputFile << "\n\n";

  outputFile.close();

  std::cout << "Работа завершена, проверьте файл output.txt";
}

int main() {
#ifdef _WIN32
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
#endif
  homework();
  return 0;
}
