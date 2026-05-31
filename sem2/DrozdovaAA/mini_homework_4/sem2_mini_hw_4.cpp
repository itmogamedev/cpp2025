#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

void printVectorToFile(std::ofstream& out_file, const std::vector<int>& vec,
                       const std::string& text) {
  out_file << text;
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out_file, " "));
  out_file << "\n";
}

void runProgram() {
  std::ofstream out_file("output.txt");

  // 1 - сгенерировать вектор из 20 целых чисел в диапазоне от -50 до 100
  std::vector<int> numbers(20);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::generate(numbers.begin(), numbers.end(),
                [&gen, &dist]() { return dist(gen); });

  printVectorToFile(out_file, numbers, "1 - generated vector: ");

  // 2 - мин и макс элементы
  auto min_and_max = std::minmax_element(numbers.begin(), numbers.end());
  out_file << "2 - min: " << *min_and_max.first
           << ", max: " << *min_and_max.second << "\n";

  // 3 - сортировка по возрастанию
  std::sort(numbers.begin(), numbers.end());
  printVectorToFile(out_file, numbers, "3 - sorted vector: ");

  // 4 - подсчет +, - и 0 эл-ов
  auto count_positive = std::count_if(numbers.begin(), numbers.end(),
                                      [](int x) { return x > 0; });
  auto count_negative = std::count_if(numbers.begin(), numbers.end(),
                                      [](int x) { return x < 0; });
  auto count_zero = std::count_if(numbers.begin(), numbers.end(),
                                  [](int x) { return x == 0; });
  out_file << "4 - positives: " << count_positive
           << ", negatives: " << count_negative << ", zeros: " << count_zero
           << "\n";

  // 5 - среднее арифм. всех эл-ов
  double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
  double arithmetic_mean = sum / numbers.size();
  out_file << "5 - arithmetic mean: " << arithmetic_mean << "\n";

  // 6 - удаление четных
  numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                               [](int x) { return x % 2 == 0; }),
                numbers.end());  // сначала сдвигаем в конец, потом отрезаем
  printVectorToFile(out_file, numbers,
                    "6 - vector after removing even numbers: ");

  // 7 - сортировка после удаления четных + новый вектор с уникальными
  std::sort(numbers.begin(), numbers.end());
  std::vector<int> unique_numbers;
  std::unique_copy(
      numbers.begin(), numbers.end(),
      std::back_inserter(unique_numbers));  // копируем только уникальные
  printVectorToFile(out_file, unique_numbers,
                    "7 - new vector with unique and sorted values: ");
  out_file.close();
}

int main() {
  runProgram();
  return 0;
}
