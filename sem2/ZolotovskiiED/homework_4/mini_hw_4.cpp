#include <algorithm>
#include <fstream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

int main() {
  std::ofstream file_output("output.txt");

  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<int> distrib(-50, 100);

  file_output << "Исходный вектор:\n";

  std::vector<int> start_lines(20);

  std::generate(start_lines.begin(), start_lines.end(), [&]() {
    return distrib(gen);
  });

  std::for_each(start_lines.begin(), start_lines.end(), [&file_output](int char_vec) {
    file_output << char_vec << " ";
  });

  file_output << "\n\nМинимальное и максимальное число:\n";
  auto min_max = std::minmax_element(start_lines.begin(), start_lines.end());
  file_output << *min_max.first << " " << *min_max.second;

  file_output << "\n\nОтсортированный по возрастанию вектор:\n";
  std::sort(start_lines.begin(), start_lines.end(), [](int a, int b) {
    return a < b;
  });
  std::for_each(start_lines.begin(), start_lines.end(), [&file_output](int char_vec) {
    file_output << char_vec << " ";
  });

  file_output << "\n\nКоличество положительных, отрицательных и нулевых элементов:\n";
  int pos = std::count_if(start_lines.begin(), start_lines.end(), [](int x) {
    return x > 0;
  });

  int neg = std::count_if(start_lines.begin(), start_lines.end(), [](int x) {
    return x < 0;
  });

  int zero = std::count_if(start_lines.begin(), start_lines.end(), [](int x) {
    return x == 0;
  });
  file_output << pos << " " << neg << " " << zero;

  file_output << "\n\nСреднее арифметическое всех элементов:\n";
  file_output << std::accumulate(start_lines.begin(), start_lines.end(), 0.0) / 20;

  file_output << "\n\nОтсортированный вектор без чётных чисел:\n";
  std::vector<int> odd_vector = start_lines;
  odd_vector.erase(std::remove_if(odd_vector.begin(), odd_vector.end(), [](int x) {
                     return x % 2 == 0;
                   }),
                   odd_vector.end());

  std::for_each(odd_vector.begin(), odd_vector.end(), [&file_output](int char_vec) {
    file_output << char_vec << " ";
  });

  file_output << "\n\nВектор без чётных чисел с уникальными значениями:\n";
  std::sort(odd_vector.begin(), odd_vector.end());

  std::vector<int> unique_vector = odd_vector;
  unique_vector.erase(std::unique(unique_vector.begin(), unique_vector.end()),
                      unique_vector.end());

  std::for_each(unique_vector.begin(), unique_vector.end(), [&file_output](int char_vec) {
    file_output << char_vec << " ";
  });

  file_output.close();

  return 0;
}
