#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

// Вывод вектора в файл
void PrintVector(const std::string& title, const std::vector<int>& vec,
                 std::ofstream& output_file) {
  output_file << "\n--- " << title << " ---\n";
  if (vec.empty()) {
    output_file << "(Вектор пуст)\n";
    return;
  }
  // Используем std::copy и ostream_iterator, чтобы избежать циклов for/while
  std::ostream_iterator<int> out(output_file, " ");
  std::cout << "Элементы: ";  // Для консольного вывода
  std::copy(vec.begin(), vec.end(), out);
  output_file << "\n";
}

// Вывод значения в файл
template <typename T>
void WriteResult(std::ofstream& output_file, const std::string& label,
                 T value) {
  output_file << "Результат " << label << ": " << value << "\n";
}

int main() {
  const std::string kOutputFile = "output.txt";
  std::ofstream output_file(kOutputFile);

  if (!output_file.is_open()) {
    std::cerr << "Ошибка: Не удалось создать файл " << kOutputFile << ".\n";
    return 1;
  }

  // Генерация случайного вектора
  const int kVectorSize = 20;
  std::vector<int> data(kVectorSize);

  // Генератор случайных чисел
  std::random_device rd;
  std::mt19937 generator(rd());
  // Диапазон: [-50, 100]
  std::uniform_int_distribution<> distribution(-50, 100);

  // Заполнение вектора (без циклов)
  std::generate(data.begin(), data.end(),
                [&]() { return distribution(generator); });

  int min_val;
  int max_val;

  // Итератор на минимальный элемент
  auto min_it = std::min_element(data.begin(), data.end());
  min_val = *min_it;
  WriteResult(output_file, "Минимальный элемент", min_val);

  // Итератор на максимальный элемент
  auto max_it = std::max_element(data.begin(), data.end());
  max_val = *max_it;
  WriteResult(output_file, "Максимальный элемент", max_val);

  std::sort(data.begin(), data.end());
  PrintVector("Вектор после сортировки", data, output_file);

  // Подсчет по условию (без циклов)
  long long positive_count =
      std::count_if(data.begin(), data.end(), [](int x) { return x > 0; });

  long long negative_count =
      std::count_if(data.begin(), data.end(), [](int x) { return x < 0; });

  long long zero_count =
      std::count_if(data.begin(), data.end(), [](int x) { return x == 0; });

  WriteResult(output_file, "Количество положительных элементов",
              positive_count);
  WriteResult(output_file, "Количество отрицательных элементов",
              negative_count);
  WriteResult(output_file, "Количество нулевых элементов", zero_count);

  // Сумма (long long для избежания переполнения)
  long long sum = std::accumulate(
      data.begin(), data.end(), 0LL,
      [](long long acc, int x) { return acc + x; });

  double average = static_cast<double>(sum) / kVectorSize;
  WriteResult(output_file, "Среднее арифметическое",
              std::round(average * 100.0) / 100.0);  // Округление

  std::vector<int> odd_numbers;

  // Фильтрация в новый вектор (проверка на нечетность)
  std::copy_if(data.begin(), data.end(), std::back_inserter(odd_numbers),
               [](int x) { return x % 2 != 0; });

  // Результат (только нечетные)
  std::vector<int>& result_v1 = odd_numbers;

  // Копия нечетных чисел
  std::vector<int> unique_odd_numbers = result_v1;

  // Сортировка для уникальности
  std::sort(unique_odd_numbers.begin(), unique_odd_numbers.end());

  // Удаление дубликатов
  auto last = std::unique(unique_odd_numbers.begin(), unique_odd_numbers.end());
  unique_odd_numbers.erase(last, unique_odd_numbers.end());

  PrintVector("Уникальные значения после фильтрации и сортировки",
              unique_odd_numbers, output_file);

  output_file.close();
  std::cout << "Обработка завершена успешно!\n";
  std::cout << "Все результаты записаны в файл: " << kOutputFile << "\n";

  return 0;
}
