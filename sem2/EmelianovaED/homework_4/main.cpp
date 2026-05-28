#include <algorithm>
#include <fstream>
#include <random>
#include <string>
#include <vector>

// Генерация вектора с 20 числами
std::vector<int> generateVector(std::mt19937& generator) {
  std::vector<int> vector_num(20);
  std::generate(vector_num.begin(), vector_num.end(), [&generator]() {
    return std::uniform_int_distribution<int>(-50, 100)(generator);
  });
  return vector_num;
}
// Запись строки в файл
void writeLine(const std::string& filename, const std::string& text) {
  std::ofstream file_out(filename, std::ios::app);
  file_out << text << std::endl;
}
// Запись вектора в файл
void writeVector(const std::string& filename, const std::vector<int>& vec) {
  std::ofstream file_out(filename, std::ios::app);
  file_out << " ";
  std::for_each(vec.begin(), vec.end(),
                [&file_out](int n) { file_out << n << " "; });
  file_out << std::endl;
}
// Минимальный и максимальные элементы
void findMinMax(const std::vector<int>& vec, const std::string& filename) {
  auto min_max = std::minmax_element(vec.begin(), vec.end());
  writeLine(filename, "Минимальное: " + std::to_string(*min_max.first));
  writeLine(filename, "Максимальное: " + std::to_string(*min_max.second));
}
// Отсортировать вектор по возрастанию
std::vector<int> sortVector(const std::vector<int>& vec,
                            const std::string& filename) {
  std::vector<int> sorted_vec = vec;
  std::sort(sorted_vec.begin(), sorted_vec.end());
  writeLine(filename, "Отсортированный вектор по возрастанию");
  writeVector(filename, sorted_vec);
  return sorted_vec;
}
// Подсчет полож., отриц. и нулевых элементов
void countEl(const std::vector<int>& vec, const std::string& filename) {
  int pos_el =
      std::count_if(vec.begin(), vec.end(), [](int n) { return n > 0; });
  int neg_el =
      std::count_if(vec.begin(), vec.end(), [](int n) { return n < 0; });
  int zer_el =
      std::count_if(vec.begin(), vec.end(), [](int n) { return n == 0; });
  writeLine(filename, "Положительные, отрицательные и нулевые элементы:");
  writeLine(filename, "Положительные: " + std::to_string(pos_el));
  writeLine(filename, "Отрицательные: " + std::to_string(neg_el));
  writeLine(filename, "Нулевые: " + std::to_string(zer_el));
}
// Среднее арифметическое
double findAverage(const std::vector<int>& vec, const std::string& filename) {
  double sum_el = 0.0;
  std::for_each(vec.begin(), vec.end(), [&sum_el](int n) { sum_el += n; });
  double avarage_el = sum_el / vec.size();
  writeLine(filename, "Среднее арифметическое");
  writeLine(filename, std::to_string(avarage_el));
  return avarage_el;
}
// Удаление четных чисел
std::vector<int> removeEven(const std::vector<int>& vec,
                            const std::string& filename) {
  std::vector<int> result_vec = vec;
  result_vec.erase(std::remove_if(result_vec.begin(), result_vec.end(),
                                  [](int n) { return n % 2 == 0; }),
                   result_vec.end());
  writeLine(filename, "Вектор после удаление четных чисел");
  writeVector(filename, result_vec);
  return result_vec;
}
// Сортировка нового вектора
void sortNewVec(const std::vector<int>& vec, const std::string& filename) {
  std::vector<int> result_vec = vec;
  std::sort(result_vec.begin(), result_vec.end());
  auto uniq_vec = std::unique(result_vec.begin(), result_vec.end());
  result_vec.erase(uniq_vec, result_vec.end());
  writeLine(filename, "Отсортированный вектор с уникальными значениями");
  writeVector(filename, result_vec);
}
void runProgram() {
  const std::string file_name = "output.txt";
  std::mt19937 generator(12);
  std::ofstream file_out(file_name);
  file_out.close();
  std::vector<int> vec_new = generateVector(generator);
  writeLine(file_name, "Исходный вектор");
  writeVector(file_name, vec_new);
  findMinMax(vec_new, file_name);
  std::vector<int> sorted_vec = sortVector(vec_new, file_name);
  countEl(sorted_vec, file_name);
  double avg_vec = findAverage(sorted_vec, file_name);
  std::vector<int> without_even = removeEven(sorted_vec, file_name);
  sortNewVec(without_even, file_name);
}
int main() {
  runProgram();
  return 0;
}
