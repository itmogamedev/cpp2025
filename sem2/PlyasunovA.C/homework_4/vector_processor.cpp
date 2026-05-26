#include "vector_processor.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>

void VectorProcessor::process() {
  output_file.open("output.txt");
  if (!output_file) {
    std::cerr << "Cannot open output.txt\n";
    return;
  }

  generateVector();
  findMinMax();
  sortAndWrite();
  countElements();
  calculateAverage();
  removeLessThanAverage();
  createUniqueVector();

  output_file.close();
}

void VectorProcessor::generateVector() {
  std::mt19937 generator(std::random_device{}());
  std::uniform_int_distribution<int> distribution(kMinValue, kMaxValue);

  numbers.resize(kVectorSize);
  std::generate(numbers.begin(), numbers.end(), [&generator, &distribution]() {
    return distribution(generator);
  });
}

void VectorProcessor::findMinMax() {
  auto min_max = std::minmax_element(numbers.begin(), numbers.end());
  output_file << "Min: " << *min_max.first << "\n";
  output_file << "Max: " << *min_max.second << "\n\n";
}

void VectorProcessor::sortAndWrite() {
  std::sort(numbers.begin(), numbers.end());
  writeVector("Sorted array:", numbers);
}

void VectorProcessor::countElements() {
  int positive_count = std::count_if(numbers.begin(), numbers.end(),
                                     [](int x) { return x > 0; });
  int negative_count = std::count_if(numbers.begin(), numbers.end(),
                                     [](int x) { return x < 0; });
  int zero_count = std::count_if(numbers.begin(), numbers.end(),
                                 [](int x) { return x == 0; });

  output_file << "Positive: " << positive_count << "\n";
  output_file << "Negative: " << negative_count << "\n";
  output_file << "Zero: " << zero_count << "\n\n";
}

void VectorProcessor::calculateAverage() {
  double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
  average = sum / numbers.size();
  output_file << "Average: " << average << "\n\n";
}

void VectorProcessor::removeLessThanAverage() {
  numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                               [this](int x) { return x < average; }),
                numbers.end());
  writeVector("After removing elements less than average:", numbers);
}

void VectorProcessor::createUniqueVector() {
  std::sort(numbers.begin(), numbers.end());
  auto last = std::unique(numbers.begin(), numbers.end());
  std::vector<int> unique_numbers(numbers.begin(), last);
  writeVector("Unique sorted vector:", unique_numbers);
}

void VectorProcessor::writeVector(const std::string& label,
                                  const std::vector<int>& vec) {
  output_file << label << "\n";
  std::for_each(vec.begin(), vec.end(),
                [this](int x) { output_file << x << " "; });
  output_file << "\n\n";
}
