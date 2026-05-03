#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>

void writeToOutput(
    const std::tuple<int, int, std::vector<int>, int, int, int, double,
                     std::vector<int>, std::vector<int>>& data) {
  auto [min, max, sorted_numbers, negative_count, zeros_count, positive_count,
        mid_arithmetic, filtered_numbers, unique_numbers] = data;

  std::ofstream output_file("output.txt");
  if (output_file.is_open()) {
    output_file << "Min: " << min << "\n";
    output_file << "Max: " << max << "\n";
    output_file << "Sorted numbers: ";
    std::for_each(sorted_numbers.begin(), sorted_numbers.end(),
                  [&](int num) { output_file << num << " "; });
    output_file << "\n";
    output_file << "Negative count: " << negative_count << "\n";
    output_file << "Zero count: " << zeros_count << "\n";
    output_file << "Positive count: " << positive_count << "\n";
    output_file << "Mid arithmetic: " << mid_arithmetic << "\n";
    output_file << "Filtered numbers (>= mid): ";
    std::for_each(filtered_numbers.begin(), filtered_numbers.end(),
                  [&](int num) { output_file << num << " "; });
    output_file << "\n";
    output_file << "Sorted unique numbers (>= mid): ";
    std::for_each(unique_numbers.begin(), unique_numbers.end(),
                  [&](int num) { output_file << num << " "; });
    output_file.close();
  } else {
    std::cerr << "Unable to open file for writing.\n";
  }
}

auto generateVector = [](auto& gen) {
  std::uniform_int_distribution<> dis(-50, 100);
  std::vector<int> vec(20);
  std::generate(vec.begin(), vec.end(), [&]() { return dis(gen); });
  return vec;
};

auto sortVector = [](const std::vector<int>& some_numbers) {
  std::vector<int> result = some_numbers;
  std::sort(result.begin(), result.end());
  return result;
};

auto findExtremes = [](const std::vector<int>& some_numbers) {
  auto [min_it, max_it] =
      std::minmax_element(some_numbers.begin(), some_numbers.end());
  return std::make_pair(*min_it, *max_it);
};

auto countPositive = [](const std::vector<int>& some_numbers) {
  return std::count_if(some_numbers.begin(), some_numbers.end(),
                       [](int num) { return num > 0; });
};

auto countNegative = [](const std::vector<int>& some_numbers) {
  return std::count_if(some_numbers.begin(), some_numbers.end(),
                       [](int num) { return num < 0; });
};

auto countZeros = [](const std::vector<int>& some_numbers) {
  return std::count_if(some_numbers.begin(), some_numbers.end(),
                       [](int num) { return num == 0; });
};

auto midArithmetic = [](const std::vector<int>& some_numbers) {
  double sum = std::accumulate(some_numbers.begin(), some_numbers.end(), 0);
  return sum / some_numbers.size();
};

auto removeThatLess = [](const std::vector<int>& some_numbers, double mid) {
  std::vector<int> result;
  std::copy_if(some_numbers.begin(), some_numbers.end(),
               std::back_inserter(result),
               [mid](int num) { return num >= mid; });
  return result;
};

auto removeDuplicates = [](const std::vector<int>& some_numbers) {
  std::vector<int> sorted = some_numbers;
  std::sort(sorted.begin(), sorted.end());
  std::vector<int> result;
  std::unique_copy(sorted.begin(), sorted.end(), std::back_inserter(result));
  return result;
};

auto processData = [](auto& gen) {
  std::vector<int> numbers = generateVector(gen);
  auto [min, max] = findExtremes(numbers);
  std::vector<int> sorted_numbers = sortVector(numbers);
  auto [negative_count, zeros_count, positive_count] =
      std::make_tuple(countNegative(sorted_numbers), countZeros(sorted_numbers),
                      countPositive(sorted_numbers));
  double mid_arithmetic = midArithmetic(sorted_numbers);
  std::vector<int> filtered_numbers = removeThatLess(numbers, mid_arithmetic);
  std::vector<int> unique_numbers =
      removeDuplicates(sortVector(filtered_numbers));

  return std::make_tuple(min, max, sorted_numbers, negative_count, zeros_count,
                         positive_count, mid_arithmetic, filtered_numbers,
                         unique_numbers);
};

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  writeToOutput(processData(gen));
  return 0;
};