#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

int main() {
  std::ofstream out_file("output.txt");
  if (!out_file.is_open()) {
    std::cerr << "Error with creating output.txt\n And it's can be my "
                 "fault...(but it's not))"
              << std::endl;
    return 1;
  }

  //////////////////////////////////////////////////////////////////////
  // Пункт 1 Сгенерировать вектор из 20 целых чисел
  //////////////////////////////////////////////////////////////////////
  std::vector<int> vec(20);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::generate(vec.begin(), vec.end(), [&dist, &gen]() { return dist(gen); });

  out_file << "Исходный вектор:\n";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out_file, " "));
  out_file << "\n\n";

  //////////////////////////////////////////////////////////////////////
  // Пункт 2 Найти и записать в файл минимальный и максимальный элементы
  //////////////////////////////////////////////////////////////////////
  auto min_in = std::min_element(vec.begin(), vec.end());
  auto max_in = std::max_element(vec.begin(), vec.end());
  out_file << "Пункт 2 - Минимальный и максимальный элементы:\n";
  out_file << "Минимальный: " << *min_in << "\n";
  out_file << "Максимальный: " << *max_in << "\n\n";

  //////////////////////////////////////////////////////////////////////
  // Пункт 3 Отсортировать вектор по возрастанию
  //////////////////////////////////////////////////////////////////////
  std::vector<int> sorted_vec = vec;  // Создаём копию
  std::sort(sorted_vec.begin(), sorted_vec.end());
  out_file << "Пункт 3 - Вектор отсортированный по возрастанию:\n";
  std::copy(sorted_vec.begin(), sorted_vec.end(),
            std::ostream_iterator<int>(out_file, " "));
  out_file << "\n\n";

  //////////////////////////////////////////////////////////////////////
  // Пункт 4 Подсчитать количество положительных, отрицательных и нулевых
  // элементов
  //////////////////////////////////////////////////////////////////////
  int positive =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x > 0; });
  int negative =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x < 0; });
  int zeros =
      std::count_if(vec.begin(), vec.end(), [](int x) { return x == 0; });

  out_file << "Пункт 4 - Количество:\n";
  out_file << "Положительных эл-тов: " << positive << "\n";
  out_file << "Отрицательных эл-тов: " << negative << "\n";
  out_file << "Нулей (нулевых эл-тов): " << zeros << "\n\n";

  //////////////////////////////////////////////////////////////////////
  // Пункт 5 Найти среднее арифметическое всех элементов
  //////////////////////////////////////////////////////////////////////
  double average = std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
  out_file << "Пункт 5 - Среднее арифметическое всех элементов: ";
  out_file << average << "\n\n";

  //////////////////////////////////////////////////////////////////////
  // Пункт 6 Удалить из вектора все чётные числа
  //////////////////////////////////////////////////////////////////////
  std::vector<int> vec_no_even = vec;
  vec_no_even.erase(std::remove_if(vec_no_even.begin(), vec_no_even.end(),
                                   [](int x) { return x % 2 == 0; }),
                    vec_no_even.end());

  out_file << "Пункт 6 - Вектор после удаления чётных чисел:\n";
  std::copy(vec_no_even.begin(), vec_no_even.end(),
            std::ostream_iterator<int>(out_file, " "));
  out_file << "\n\n";

  //////////////////////////////////////////////////////////////////////
  // Пункт 7 Отсортировать вектор, полученный после шага 6
  //////////////////////////////////////////////////////////////////////
  std::vector<int> sort_and_uniq_vec = vec_no_even;
  std::sort(sort_and_uniq_vec.begin(), sort_and_uniq_vec.end());
  auto last = std::unique(sort_and_uniq_vec.begin(), sort_and_uniq_vec.end());
  sort_and_uniq_vec.erase(last, sort_and_uniq_vec.end());

  out_file << "Пункт 7 - Отсортированный вектор с уникальными значениями:\n";
  std::copy(sort_and_uniq_vec.begin(), sort_and_uniq_vec.end(),
            std::ostream_iterator<int>(out_file, " "));
  out_file << "\n";

  out_file.close();
  return 0;
}
