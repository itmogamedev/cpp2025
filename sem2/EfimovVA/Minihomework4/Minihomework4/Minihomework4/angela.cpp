#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <string>
#include <vector>

class VectorProcessor {
 private:
  std::vector<int> numbers;
  std::string output_filename;

  void writeVectorToFile(std::ofstream& out_file, const std::string& title,
                         const std::vector<int>& vec);

 public:
  VectorProcessor(const std::string& out_file);

  void processVector();
};

VectorProcessor::VectorProcessor(const std::string& out_file) {
  output_filename = out_file;
}

void VectorProcessor::writeVectorToFile(std::ofstream& out_file,
                                        const std::string& title,
                                        const std::vector<int>& vec) {
  out_file << title << "\n";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(out_file, " "));
  out_file << "\n\n";
}

void VectorProcessor::processVector() {
  std::ofstream out_file(output_filename);
  if (!out_file.is_open()) {
    std::cout << "Ti xuety kakou eto sdelal " << output_filename << '\n';
    return;
  }

  const int vector_size = 20;
  const int min_val = -50;
  const int max_val = 100;

  numbers.resize(vector_size);

  // Генерим 20 чисел в диапазоне от -50 до 100
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(min_val, max_val);

  std::generate(numbers.begin(), numbers.end(),
                [&dist, &gen]() { return dist(gen); });

  writeVectorToFile(out_file, "Generated vector", numbers);

  // Ищем минимальные и максимальные элементы
  auto minmax = std::minmax_element(numbers.begin(), numbers.end());
  out_file << "Min and Max\n";
  out_file << "Min: " << *minmax.first << "\nMax: " << *minmax.second << "\n\n";

  // Сортим вектор
  std::sort(numbers.begin(), numbers.end());
  writeVectorToFile(out_file, "Sorted vector", numbers);

  // Считаем положительных, отрицательных и нулевых элементов (ебучие нарды)
  int positive_count = std::count_if(numbers.begin(), numbers.end(),
                                     [](int n) { return n > 0; });
  int negative_count = std::count_if(numbers.begin(), numbers.end(),
                                     [](int n) { return n < 0; });
  int zero_count = std::count_if(numbers.begin(), numbers.end(),
                                 [](int n) { return n == 0; });

  out_file << "Counts\n";
  out_file << "Positive: " << positive_count << "\n";
  out_file << "Negative: " << negative_count << "\n";
  out_file << "Zeroes: " << zero_count << "\n\n";

  // Чекаем среднее арифметическое
  double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
  double mean = sum / numbers.size();

  out_file << "Arithmetic Mean\n";
  out_file << mean << "\n\n";

  // ВЫКИДЫВАЕМ В ГАЗОВУЮ КАМЕРУ ЧИСЛА МЕНЬШЕ АРИФМЕТИЧЕСКОГО)))
  numbers.erase(
      std::remove_if(numbers.begin(), numbers.end(),
                     [mean](int n) { return static_cast<double>(n) < mean; }),
      numbers.end());
  writeVectorToFile(out_file, "Vector after removing elements < mean", numbers);

  // Сортим новые числа
  std::sort(numbers.begin(), numbers.end());
  std::vector<int> unique_numbers;

  std::unique_copy(numbers.begin(), numbers.end(),
                   std::back_inserter(unique_numbers));

  writeVectorToFile(out_file, "Sorted unique vector", unique_numbers);

  out_file.close();
  std::cout << "Yayyayyay " << output_filename
            << " GO CHECK THE FYLE EINSTEIN0))).\n";
}

int main() {
  VectorProcessor processor("output.txt");
  processor.processVector();

  return 0;
}
