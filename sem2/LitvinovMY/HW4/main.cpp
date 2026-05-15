#include <algorithm>
#include <chrono>
#include <fstream>
#include <iterator>
#include <numeric>
#include <random>

const int kVectorSize = 20;
const int kMin = -50;
const int kMax = 100;

void write_numbers(std::vector<int>& numbers, std::ofstream& output) {
  std::for_each(numbers.begin(), numbers.end(),
                [&](const int& n) { output << n << ' '; });
  output << '\n';
}

void task4(std::mt19937& rng, std::ofstream& output) {
  // 1. Generate numbers

  std::vector<int> numbers(kVectorSize);
  std::uniform_int_distribution<int> distr(kMin, kMax);
  std::generate(numbers.begin(), numbers.end(), [&] { return distr(rng); });

  // 2. Find min and max elements

  output << *std::min_element(numbers.begin(), numbers.end()) << ' ';
  output << *std::max_element(numbers.begin(), numbers.end()) << '\n';

  // 3. Sort the vector

  std::sort(numbers.begin(), numbers.end());

  write_numbers(numbers, output);

  // 4. Count the positive, negative and neutral elements

  int pos = 0;
  int neg = 0;
  int zer = 0;
  std::for_each(numbers.begin(), numbers.end(), [&](const int& n) {
    if (n > 0)
      pos++;
    else if (n < 0)
      neg++;
    else
      zer++;
  });

  output << pos << ' ' << neg << ' ' << zer << '\n';

  // 5. Find the average

  int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
  float avg = static_cast<float>(sum) / numbers.size();

  output << avg << '\n';
  // 6.a. Remove all the even numbers

  std::erase_if(numbers, [](int& n) { return !(n % 2); });

  write_numbers(numbers, output);

  // 7. Sort the vector again; create a vector only containing unique elements
  std::vector<int> unique_numbers{*numbers.begin()};
  std::for_each(numbers.begin() + 1, numbers.end(), [&](int& n) {
    if (*unique_numbers.rbegin() != n) unique_numbers.push_back(n);
  });

  write_numbers(unique_numbers, output);
}

int main() {
  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  std::ofstream output("output.txt");

  task4(rng, output);

  output.close();

  return 0;
}