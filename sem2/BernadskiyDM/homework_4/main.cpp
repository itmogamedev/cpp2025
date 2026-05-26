#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <iterator>

int main() {
  std::ofstream outfile("output.txt");
  if (!outfile.is_open()) {
    std::cerr << "Ошибка открытия файла!" << std::endl;
    return 1;
  }

  // 1. Генерация вектора (20 чисел от -50 до 100)
  std::vector<int> vec(20);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(-50, 100);

  std::generate(vec.begin(), vec.end(), [&]() { return dist(gen); });

  // Вспомогательная лямбда для вывода вектора в файл без циклов
  auto print_vec = [&](const std::string& label, const std::vector<int>& v) {
    outfile << label << ": ";
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(outfile, " "));
    outfile << "\n";
  };

  // 2. Поиск минимального и максимального элементов
  auto [min_it, max_it] = std::minmax_element(vec.begin(), vec.end());
  outfile << "2. Минимум: " << *min_it << ", Максимум: " << *max_it << "\n";

  // 3. Сортировка по возрастанию
  std::sort(vec.begin(), vec.end());
  print_vec("3. Отсортированный вектор", vec);

  // 4. Подсчет положительных, отрицательных и нулевых элементов
  long pos = std::count_if(vec.begin(), vec.end(), [](int n) { return n > 0; });
  long neg = std::count_if(vec.begin(), vec.end(), [](int n) { return n < 0; });
  long zero = std::count_if(vec.begin(), vec.end(), [](int n) { return n == 0; });
  outfile << "4. Положительных: " << pos << ", Отрицательных: " << neg << ", Нулевых: " << zero << "\n";

  // 5. Среднее арифметическое
  double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
  double avg = sum / vec.size();
  outfile << "5. Среднее арифметическое: " << avg << "\n";

  // 6. ВАРИАНТ 1: Удаление всех четных чисел
  vec.erase(std::remove_if(vec.begin(), vec.end(), [](int n) {
    return n % 2 == 0;
  }), vec.end());
  print_vec("6. Вектор без четных чисел", vec);

  // 7. Создание нового вектора с уникальными значениями
  // Сначала сортируем (т.к. после шага 6 порядок мог быть важен, но для unique нужна сортировка)
  std::sort(vec.begin(), vec.end());
  std::vector<int> unique_vec = vec;
  unique_vec.erase(std::unique(unique_vec.begin(), unique_vec.end()), unique_vec.end());
  print_vec("7. Только уникальные значения", unique_vec);

  outfile.close();
  std::cout << "Минидомашка 4 выполнена! Результаты в output.txt" << std::endl;

  return 0;
}