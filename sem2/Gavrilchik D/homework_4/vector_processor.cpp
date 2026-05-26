#include "vector_processor.h"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <numeric>
#include <random>

VectorProcessor::VectorProcessor(const std::string& output_file_name)
    : output_file_name(output_file_name) {}

void VectorProcessor::run() {
  std::ofstream output_file(output_file_name);

  std::vector<int> numbers = generateNumbers();

  output_file << "Generated vector:\n";
  writeVector(output_file, numbers);

  output_file << "\nMinimum value:\n";
  output_file << getMinValue(numbers) << '\n';

  output_file << "\nMaximum value:\n";
  output_file << getMaxValue(numbers) << '\n';

  std::vector<int> sorted_numbers = sortNumbers(numbers);

  output_file << "\nSorted vector:\n";
  writeVector(output_file, sorted_numbers);

  output_file << "\nPositive numbers count:\n";
  output_file << countPositiveNumbers(numbers) << '\n';

  output_file << "\nNegative numbers count:\n";
  output_file << countNegativeNumbers(numbers) << '\n';

  output_file << "\nZero numbers count:\n";
  output_file << countZeroNumbers(numbers) << '\n';

  double average_value = getAverageValue(numbers);

  output_file << "\nAverage value:\n";
  output_file << average_value << '\n';

  std::vector<int> filtered_numbers =
      removeLessThanAverage(numbers, average_value);

  output_file << "\nVector after removing numbers less than average:\n";
  writeVector(output_file, filtered_numbers);

  std::vector<int> unique_numbers = getUniqueSortedNumbers(filtered_numbers);

  output_file << "\nUnique sorted vector:\n";
  writeVector(output_file, unique_numbers);
}

std::vector<int> VectorProcessor::generateNumbers() const {
  std::vector<int> numbers(20);

  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution<int> distribution(-50, 100);

  std::generate(numbers.begin(), numbers.end(),
                [&generator, &distribution]() {
                  return distribution(generator);
                });

  return numbers;
}

int VectorProcessor::getMinValue(const std::vector<int>& numbers) const {
  return *std::min_element(numbers.begin(), numbers.end());
}

int VectorProcessor::getMaxValue(const std::vector<int>& numbers) const {
  return *std::max_element(numbers.begin(), numbers.end());
}

double VectorProcessor::getAverageValue(const std::vector<int>& numbers) const {
  int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

  return static_cast<double>(sum) / static_cast<double>(numbers.size());
}

int VectorProcessor::countPositiveNumbers(
    const std::vector<int>& numbers) const {
  return static_cast<int>(
      std::count_if(numbers.begin(), numbers.end(),
                    [](int number) { return number > 0; }));
}

int VectorProcessor::countNegativeNumbers(
    const std::vector<int>& numbers) const {
  return static_cast<int>(
      std::count_if(numbers.begin(), numbers.end(),
                    [](int number) { return number < 0; }));
}

int VectorProcessor::countZeroNumbers(const std::vector<int>& numbers) const {
  return static_cast<int>(
      std::count_if(numbers.begin(), numbers.end(),
                    [](int number) { return number == 0; }));
}

std::vector<int> VectorProcessor::sortNumbers(
    const std::vector<int>& numbers) const {
  std::vector<int> sorted_numbers = numbers;

  std::sort(sorted_numbers.begin(), sorted_numbers.end());

  return sorted_numbers;
}

std::vector<int> VectorProcessor::removeLessThanAverage(
    const std::vector<int>& numbers,
    double average_value) const {
  std::vector<int> filtered_numbers = numbers;

  filtered_numbers.erase(
      std::remove_if(filtered_numbers.begin(), filtered_numbers.end(),
                     [average_value](int number) {
                       return number < average_value;
                     }),
      filtered_numbers.end());

  return filtered_numbers;
}

std::vector<int> VectorProcessor::getUniqueSortedNumbers(
    const std::vector<int>& numbers) const {
  std::vector<int> unique_numbers = numbers;

  std::sort(unique_numbers.begin(), unique_numbers.end());

  auto last_unique =
      std::unique(unique_numbers.begin(), unique_numbers.end());

  unique_numbers.erase(last_unique, unique_numbers.end());

  return unique_numbers;
}

void VectorProcessor::writeVector(std::ofstream& output_file,
                                  const std::vector<int>& numbers) const {
  std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<int>(output_file, " "));

  output_file << '\n';
}