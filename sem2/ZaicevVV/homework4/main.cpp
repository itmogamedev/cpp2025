#include <algorithm>
#include <fstream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

void PrintVector(const std::vector<int>& values, std::ofstream& output) {
  std::copy(values.begin(), values.end(),
            std::ostream_iterator<int>(output, " "));
  output << '\n';
}

int main() {
  constexpr int kVectorSize = 20;
  constexpr int kMinValue = -50;
  constexpr int kMaxValue = 100;

  std::mt19937 generator(std::random_device{}());
  std::uniform_int_distribution<int> distribution(kMinValue, kMaxValue);

  std::vector<int> numbers(kVectorSize);
  std::generate(numbers.begin(), numbers.end(),
                [&generator, &distribution]() {
                  return distribution(generator);
                });

  std::ofstream output("output.txt");
  if (!output.is_open()) {
    return 1;
  }

  const auto minmax = std::minmax_element(numbers.begin(), numbers.end());
  output << "Min: " << *minmax.first << '\n';
  output << "Max: " << *minmax.second << '\n';

  std::sort(numbers.begin(), numbers.end());
  output << "Sorted vector: ";
  PrintVector(numbers, output);

  const int positive_count = std::count_if(
      numbers.begin(), numbers.end(), [](int value) { return value > 0; });
  const int negative_count = std::count_if(
      numbers.begin(), numbers.end(), [](int value) { return value < 0; });
  const int zero_count = std::count(numbers.begin(), numbers.end(), 0);

  output << "Positive count: " << positive_count << '\n';
  output << "Negative count: " << negative_count << '\n';
  output << "Zero count: " << zero_count << '\n';

  const double average =
      static_cast<double>(std::accumulate(numbers.begin(), numbers.end(), 0)) /
      numbers.size();
  output << "Average: " << average << '\n';

  numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                               [](int value) { return value % 2 == 0; }),
                numbers.end());
  output << "Vector without even numbers: ";
  PrintVector(numbers, output);

  std::sort(numbers.begin(), numbers.end());

  std::vector<int> unique_numbers;
  std::unique_copy(numbers.begin(), numbers.end(),
                   std::back_inserter(unique_numbers));

  output << "Unique sorted vector: ";
  PrintVector(unique_numbers, output);

  return 0;
}
