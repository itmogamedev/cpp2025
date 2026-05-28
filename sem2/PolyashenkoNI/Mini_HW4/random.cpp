#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <iterator>

int main() {
  //Создаём вектор из 20 элементов
  std::vector<int> vec(20);

  //Инициализируем генератор случайных чисел mt19937
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);

  //Генерируем случайные числа с помощью std::generate и лямбды
  std::generate(vec.begin(), vec.end(), [&gen, &dist]() {
    return dist(gen);
  });

  //Открываем файл для записи результатов
  std::ofstream outputFile("output.txt");
  if (!outputFile.is_open()) {
    std::cerr << "Error: Could not open output.txt" << std::endl;
    return 1;
  }

  //Находим минимум и максимум
  auto minIt = std::min_element(vec.begin(), vec.end());
  auto maxIt = std::max_element(vec.begin(), vec.end());
  std::cout << "Min and Max" << std::endl;
  std::cout << "Min: " << *minIt << ", Max: " << *maxIt << std::endl << std::endl;

  std::cout << "Min: " << *minIt << ", Max: " << *maxIt << std::endl;

  //Сортируем вектор по возрастанию
  std::sort(vec.begin(), vec.end());

  std::cout << "Sorted vector" << std::endl;
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl << std::endl;

  outputFile << "Sorted vector:" << std::endl;
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(outputFile, " "));
  outputFile << std::endl << std::endl;

  //Считаем положительные, отрицательные и нули
  int positive = std::count_if(vec.begin(), vec.end(), [](int x) { return x > 0; });
  int negative = std::count_if(vec.begin(), vec.end(), [](int x) { return x < 0; });
  int zeros = std::count_if(vec.begin(), vec.end(), [](int x) { return x == 0; });

  std::cout << "Counts" << std::endl;
  std::cout << "Positive: " << positive << ", Negative: " << negative << ", Zero: " << zeros << std::endl << std::endl;

  outputFile << "Positive: " << positive << std::endl;
  outputFile << "Negative: " << negative << std::endl;
  outputFile << "Zero: " << zeros << std::endl << std::endl;

  //Вычисляем среднее арифметическое
  double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
  double average = sum / vec.size();

  std::cout << "Average" << std::endl;
  std::cout << "Average: " << average << std::endl << std::endl;

  outputFile << "Average: " << average << std::endl << std::endl;

  //Удаляем все чётные числа
  vec.erase(std::remove_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; }), vec.end());

  std::cout << "Vector after removing even numbers" << std::endl;
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl << std::endl;

  outputFile << "Vector after removing even numbers:" << std::endl;
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(outputFile, " "));
  outputFile << std::endl << std::endl;

  //Сортируем и оставляем только уникальные значения
  std::sort(vec.begin(), vec.end());
  auto last = std::unique(vec.begin(), vec.end());
  vec.erase(last, vec.end());

  std::cout << "Sorted unique vector" << std::endl;
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  outputFile << "Sorted unique vector:" << std::endl;
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(outputFile, " "));
  outputFile << std::endl;

  outputFile.close();

  std::cout << "All results written to output.txt" << std::endl;

  return 0;
}