#include <algorithm>
#include <fstream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

std::vector<int> generateVector() {
  std::vector<int> numbers(20);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::generate(numbers.begin(), numbers.end(),
                [&dist, &gen]() { return dist(gen); });
  return numbers;
}

void printVector(std::ofstream& out, const std::string& title,
                 const std::vector<int>& numbers) {
  out << title << '\n';
  if (numbers.empty()) {
    out << "empty\n\n";
    return;
  }
  std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<int>(out, " "));
  out << "\n\n";
}

void printMinMax(std::ofstream& out, const std::vector<int>& numbers) {
  auto result = std::minmax_element(numbers.begin(), numbers.end());
  out << "Minimum element: " << *result.first << '\n';
  out << "Maximum element: " << *result.second << "\n\n";
}

std::vector<int> getSortedVector(std::vector<int> numbers) {
  std::sort(numbers.begin(), numbers.end());
  return numbers;
}

void printCounts(std::ofstream& out, const std::vector<int>& numbers) {
  int positive = static_cast<int>(std::count_if(numbers.begin(), numbers.end(),
                                                [](int x) { return x > 0; }));
  int negative = static_cast<int>(std::count_if(numbers.begin(), numbers.end(),
                                                [](int x) { return x < 0; }));
  int zero = static_cast<int>(std::count(numbers.begin(), numbers.end(), 0));

  out << "Positive elements: " << positive << '\n';
  out << "Negative elements: " << negative << '\n';
  out << "Zero elements: " << zero << "\n\n";
}

double getAverage(const std::vector<int>& numbers) {
  int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
  return static_cast<double>(sum) / numbers.size();
}

void printAverage(std::ofstream& out, double average) {
  out << "Average value: " << average << "\n\n";
}

std::vector<int> removeLessThanAverage(std::vector<int> numbers,
                                       double average) {
  numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                               [average](int x) { return x < average; }),
                numbers.end());
  return numbers;
}

std::vector<int> getUniqueSortedVector(std::vector<int> numbers) {
  std::sort(numbers.begin(), numbers.end());
  numbers.erase(std::unique(numbers.begin(), numbers.end()), numbers.end());
  return numbers;
}

void writeResult() {
  std::ofstream out("output.txt");

  std::vector<int> numbers = generateVector();
  std::vector<int> sortedNumbers = getSortedVector(numbers);

  double average = getAverage(numbers);

  std::vector<int> afterStepSix = removeLessThanAverage(numbers, average);
  std::vector<int> uniqueVector = getUniqueSortedVector(afterStepSix);

  printVector(out, "Generated vector:", numbers);
  printMinMax(out, numbers);
  printVector(out, "Sorted vector:", sortedNumbers);
  printCounts(out, numbers);
  printAverage(out, average);
  printVector(
      out, "Vector after deleting elements less than average:", afterStepSix);
  printVector(out, "Unique sorted vector after step 6:", uniqueVector);
}

int main() {
  writeResult();
  return 0;
}