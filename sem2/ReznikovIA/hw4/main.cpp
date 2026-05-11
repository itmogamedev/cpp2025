#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

std::vector<int> generateVector();
void workWithArray(std::vector<int>& numbers);
void writeToFile(const std::vector<int>& data,
                 const std::string& outputFileName);
void writeToFile(const std::string& data, const std::string& outputFileName);
void writeToFile(const double& data, const std::string& outputFileName);

void clearFile(const std::string& fileName);

int main() {
  std::vector<int> numbers = generateVector();
  workWithArray(numbers);
  return 0;
}

void workWithArray(std::vector<int>& numbers) {
  std::string fileName = "output.txt";
  clearFile(fileName);

  auto maxElemIt = std::max_element(numbers.cbegin(), numbers.cend());
  writeToFile("max: " + std::to_string((*maxElemIt)), fileName);
  auto minElemIt = std::min_element(numbers.cbegin(), numbers.cend());
  writeToFile("min: " + std::to_string((*minElemIt)), fileName);

  std::sort(numbers.begin(), numbers.end());
  writeToFile("sorted", fileName);
  writeToFile(numbers, fileName);

  int positiveCount =
      std::count_if(numbers.cbegin(), numbers.cend(),
                    [](int number) -> bool { return number > 0; });
  writeToFile("+: " + std::to_string(positiveCount), fileName);
  int negativeCount =
      std::count_if(numbers.cbegin(), numbers.cend(),
                    [](int number) -> bool { return number < 0; });
  writeToFile("-: " + std::to_string(negativeCount), fileName);

  int zeroCount = std::count_if(numbers.cbegin(), numbers.cend(),
                                [](int number) -> bool { return number == 0; });
  writeToFile("0: " + std::to_string(zeroCount), fileName);

  double mean = std::accumulate(numbers.cbegin(), numbers.cend(), 0) /
                static_cast<double>(numbers.size());
  writeToFile("arithmetic mean: " + std::to_string(mean), fileName);

  auto newEnd = std::remove_if(numbers.begin(), numbers.end(),
                               [](int num) { return num % 2 == 0; });
  numbers.erase(newEnd, numbers.end());
  writeToFile("only odd", fileName);
  writeToFile(numbers, fileName);

  std::sort(numbers.begin(), numbers.end());
  std::vector<int> uniqueNumbers;
  std::unique_copy(numbers.begin(), numbers.end(),
                   std::back_inserter(uniqueNumbers));
  writeToFile("sorted unique", fileName);
  writeToFile(uniqueNumbers, fileName);
}

std::vector<int> generateVector() {
  std::vector<int> nums(20);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::generate(nums.begin(), nums.end(),
                [&dist, &gen]() { return dist(gen); });
  return nums;
}

void clearFile(const std::string& fileName) {
  std::ofstream out(fileName);
  if (out.is_open()) {
  }
  out.close();
}

void writeToFile(const std::string& data, const std::string& fileName) {
  std::ofstream out(fileName, std::ios::app);
  if (out.is_open()) {
    out << data << std::endl;
  }
  out.close();
}

void writeToFile(const double& data, const std::string& fileName) {
  std::ofstream out(fileName, std::ios::app);
  if (out.is_open()) {
    out << data << std::endl;
  }
  out.close();
}

void writeToFile(const std::vector<int>& data,
                 const std::string& outputFileName) {
  std::for_each(data.cbegin(), data.cend(),
                [&data, &outputFileName](const int num) {
                  writeToFile(std::to_string(num), outputFileName);
                });
}
