#include "VectorWork.h"

#include <algorithm>
#include <iterator>
#include <numeric>
#include <random>

VectorWork::VectorWork(const std::string& filename) : output_file(filename) {
  mean_value = 0.0;
}

VectorWork::~VectorWork() {
  if (output_file.is_open()) {
    output_file.close();
  }
}

void VectorWork::runAllSteps() {
  if (!output_file.is_open()) {
    return;
  }

  generateVector();
  findMixMax();
  sortAndWrite();
  countElements();
  calculateMean();
  removeBelowMean();
  extractUnique();
}

void VectorWork::writeVectorToFile(const std::vector<int>& vec,
                                   const std::string& message) {
  output_file << message << ":\n";
  std::copy(vec.begin(), vec.end(),
            std::ostream_iterator<int>(output_file, " "));
  output_file << "\n\n";
}

void VectorWork::generateVector() {
  numbers.resize(20);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(-50, 100);

  std::generate(numbers.begin(), numbers.end(),
                [&gen, &dist]() { return dist(gen); });

  writeVectorToFile(numbers, "1. Сгенирированный исходный вектор");
}

void VectorWork::findMixMax() {
  auto [min_it, max_it] = std::minmax_element(numbers.begin(), numbers.end());
  output_file << "2. Минимальный и максимальный элемент:\n";
  output_file << "Min: " << *min_it << "\nMax: " << *max_it << "\n\n";
}

void VectorWork::sortAndWrite() {
  std::sort(numbers.begin(), numbers.end());
  writeVectorToFile(numbers, "3. Отсортированный вектор");
}

void VectorWork::countElements() {
  int pos_count = std::count_if(numbers.begin(), numbers.end(),
                                [](int num) { return num > 0; });
  int neg_count = std::count_if(numbers.begin(), numbers.end(),
                                [](int num) { return num < 0; });
  int zero_count = std::count_if(numbers.begin(), numbers.end(),
                                 [](int num) { return num == 0; });

  output_file << "4. Подсчет эллементов:\n";
  output_file << "Положительные: " << pos_count << "\n";
  output_file << "Отрицательные: " << neg_count << "\n";
  output_file << "Нули: " << zero_count << "\n\n";
}

void VectorWork::calculateMean() {
  double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
  mean_value = sum / numbers.size();

  output_file << "5. Среднее значение:\n";
  output_file << "Mean: " << mean_value << "\n\n";
}

void VectorWork::removeBelowMean() {
  auto remove_it = std::remove_if(numbers.begin(), numbers.end(),
                                  [this](int num) { return num < mean_value; });
  numbers.erase(remove_it, numbers.end());
  writeVectorToFile(numbers,
                    "6. Вектор после удаления элементов ниже среднего");
}

void VectorWork::extractUnique() {
  std::sort(numbers.begin(), numbers.end());
  std::vector<int> unique_numbers;

  std::unique_copy(numbers.begin(), numbers.end(),
                   std::back_inserter(unique_numbers));
  writeVectorToFile(unique_numbers, "7. Вектор с уникальными элементами");
}
