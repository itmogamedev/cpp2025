#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <set>
#include <vector>

void solve() {
  std::mt19937 rand(
      std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> seg(-50, 100);

  int size_of_vector = 20;
  std::vector<int> numbers(size_of_vector);
  std::ofstream file;
  file.open("output.txt");

  auto print = [&]() {
    std::copy(numbers.begin(), numbers.end(),
              std::ostream_iterator<int>(file, " "));
    file << '\n';
  };

  auto gen = [&]() {
    int rand_number = seg(rand);
    return rand_number;
  };

  auto isEven = [](int n) { return !(n % 2); };

  std::generate(numbers.begin(), numbers.end(), gen);
  std::sort(numbers.begin(), numbers.end());
  file << "Min: " << numbers[0] << ", Max: " << numbers[numbers.size() - 1]
       << "\nSort:\n";
  print();

  int neg_numb, zeroes, pos_numb;
  neg_numb =
      std::upper_bound(numbers.begin(), numbers.end(), -1) - numbers.begin();
  zeroes =
      (std::upper_bound(numbers.begin(), numbers.end(), 0) - numbers.begin()) -
      (std::lower_bound(numbers.begin(), numbers.end(), 0) - numbers.begin());
  pos_numb =
      numbers.size() -
      (std::lower_bound(numbers.begin(), numbers.end(), 1) - numbers.begin());
  file << "Negative numbers: " << neg_numb << "\nZeroes: " << zeroes
       << "\nPositive numbers: " << pos_numb << '\n';

  float sum;
  sum = std::accumulate(numbers.begin(), numbers.end(), 0);
  file << "Arithmetic mean: " << sum / size_of_vector << '\n';

  std::erase_if(numbers, isEven);
  file << "Deleting even numbers:\n";
  print();

  file << "Unique numbers:\n";
  std::set<int> set_numbers(numbers.begin(), numbers.end());
  numbers = std::vector(set_numbers.begin(), set_numbers.end());
  print();
}

int main() {
  solve();
  return 0;
}
