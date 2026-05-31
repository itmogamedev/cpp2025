#include <windows.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  std::ofstream out("output.txt");
  if (!out) {
    std::cerr << "Не удалось открыть файл output.txt\n";
    return 1;
  }

  // 1. Генерация вектора из 20 целых чисел от -50 до 100
  std::vector<int> vec(20);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(-50, 100);

  std::generate(vec.begin(), vec.end(), [&dist, &gen]() { return dist(gen); });

  out << "1. Сгенерированный вектор:\n";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << "\n\n";

  // 2. Минимальный и максимальный элементы
  std::pair<std::vector<int>::iterator, std::vector<int>::iterator> minmax =
      std::minmax_element(vec.begin(), vec.end());

  out << "2. Минимальный элемент: " << *minmax.first << "\n";
  out << "   Максимальный элемент: " << *minmax.second << "\n\n";

  // 3. Сортировка по возрастанию и запись
  std::sort(vec.begin(), vec.end());
  out << "3. Отсортированный вектор по возрастанию:\n";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << "\n\n";

  // 4. Подсчёт положительных, отрицательных и нулевых элементов
  int positive =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x > 0; });
  int negative =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x < 0; });
  int zero =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x == 0; });

  out << "4. Количество положительных: " << positive << "\n";
  out << "   Количество отрицательных: " << negative << "\n";
  out << "   Количество нулевых: " << zero << "\n\n";

  // 5. Среднее арифметическое всех элементов
  double average = std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
  out << "5. Среднее арифметическое: " << average << "\n\n";

  // 6. ВАРИАНТ 2: Удаление чисел, которые меньше среднего арифметического
  vec.erase(std::remove_if(vec.begin(), vec.end(),
                           [average](int x) { return x < average; }),
            vec.end());

  out << "6. Вектор после удаления чисел, меньших среднего арифметического ("
      << average << "):\n";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out, " "));
  out << "\n\n";

  // 7. Сортировка вектора и создание нового вектора с уникальными значениями
  std::sort(vec.begin(), vec.end());
  std::vector<int> unique_vec;
  std::unique_copy(vec.begin(), vec.end(), std::back_inserter(unique_vec));

  out << "7. Отсортированный вектор с уникальными значениями:\n";
  std::copy(unique_vec.begin(), unique_vec.end(),
            std::ostream_iterator<int>(out, " "));
  out << "\n";

  std::cout << "Результаты записаны в output.txt\n";
  return 0;
}
