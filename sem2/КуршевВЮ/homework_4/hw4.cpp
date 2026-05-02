#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

int main() {
  // 1. Генерация случайного вектора
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::vector<int> vec(20);
  std::generate(vec.begin(), vec.end(), [&]() { return dist(rng); });

  // Исходный вектор
  std::vector<int> original = vec;

  std::ofstream output("output.txt");

  auto print_vector = [&output](const std::string& title, const auto& vec) {
    output << title << '\n';
    for (const auto& elem : vec) {
      output << elem << '\n';
    }
    output << '\n';
  };

  print_vector("Исходный вектор: ", original);

  // 2. Минимум и максимум
  auto minmax = std::minmax_element(vec.begin(), vec.end());
  output << "Минимальный элемент: " << *minmax.first << "\n";
  output << "Максимальный элемент: " << *minmax.second<< "\n\n";

  // 3. Сортировка по возрастанию
  std::sort(vec.begin(), vec.end());
  print_vector("Отсортированный вектор: ", vec);

  // 4. Количество положительных, отрицательных и нулей
  int positive =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x > 0; });
  int negative =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x < 0; });
  int zero =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x == 0; });
  output << "Положительных: " << positive << "\n";
  output << "Отрицательных: " << negative << "\n";
  output << "Нулевых: " << zero << "\n\n";

  // Шаг 5. Среднее арифметическое
  double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
  double average = sum / vec.size();
  output << "Среднее арифметическое: " << average << "\n\n";

  // 6. Удаление чётных чисел
  vec.erase(
      std::remove_if(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; }),
      vec.end());
  print_vector("После удаления чётных чисел: ", vec);

  // 7. Сортировка и создание вектора уникальных значений
  std::sort(vec.begin(), vec.end());
  std::vector<int> unique_vec;
  std::unique_copy(vec.begin(), vec.end(), std::back_inserter(unique_vec));
  print_vector("Новый вектор с уникальными значениями: ", unique_vec);

  output.close();
  std::cout << "Результаты записаны в output.txt";

}