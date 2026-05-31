#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

int main() {
  std::ofstream outFile("output.txt");

  // Сгенерировать вектор из 20 чисел от -50 до 100 через std::generate и std::mt19937
  std::vector<int> v(20);
  std::mt19937 gen(12345);
  std::uniform_int_distribution<int> dis(-50, 100);

  std::generate(v.begin(), v.end(), [&gen, &dis]() {
    return dis(gen);
    });

  auto printVector = [&outFile](const std::vector<int>& vec, std::string label) {
    outFile << label << ": ";
    std::for_each(vec.begin(), vec.end(), [&outFile](int x) {
      outFile << x << " ";
      });
    outFile << "\n";
    };

  printVector(v, "Generated vector");

  // Найти минимальный и максимальный элементы
  auto minMaxIt = std::minmax_element(v.begin(), v.end());
  outFile << "Min element: " << *minMaxIt.first << "\n";
  outFile << "Max element: " << *minMaxIt.second << "\n";

  // Отсортировать вектор по возрастанию
  std::sort(v.begin(), v.end());
  printVector(v, "Sorted vector");

  // Подсчитать количество положительных, отрицательных и нулевых элементов
  long posCount = std::count_if(v.begin(), v.end(), [](int x) { return x > 0; });
  long negCount = std::count_if(v.begin(), v.end(), [](int x) { return x < 0; });
  long zeroCount = std::count_if(v.begin(), v.end(), [](int x) { return x == 0; });

  outFile << "Positive count: " << posCount << "\n";
  outFile << "Negative count: " << negCount << "\n";
  outFile << "Zero count: " << zeroCount << "\n";

  // Найти среднее арифметическое всех элементов
  double sum = std::accumulate(v.begin(), v.end(), 0.0);
  double average = sum / v.size();
  outFile << "Average: " << average << "\n";

  // ВАРИАНТ 1: Удалить из вектора все чётные числа
  auto newEnd = std::remove_if(v.begin(), v.end(), [](int x) {
    return x % 2 == 0;
    });
  v.erase(newEnd, v.end());
  printVector(v, "After removing even numbers");

  // Отсортировать полученный вектор и оставить только уникальные значения
  std::sort(v.begin(), v.end()); 
  auto uniqueEnd = std::unique(v.begin(), v.end());
  std::vector<int> uniqueV(v.begin(), uniqueEnd); // Создаем новый вектор на основе уникальных значений

  printVector(uniqueV, "Unique numbers vector");

  outFile.close();
  std::cout << "Done!" << std::endl;
  return 0;
}
