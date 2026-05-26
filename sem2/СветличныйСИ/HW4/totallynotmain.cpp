#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iterator>

int totallynotmain()
{
  std::ofstream fout("output.txt");

  if (!fout.is_open())
  {
    std::cerr << "Cannot open output.txt\n";
    return 1;
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(-50, 100);

  std::vector<int> numbers(20);

  std::generate(
    numbers.begin(),
    numbers.end(),
    [&]() {
      return dist(gen);
    }
  );

  fout << "Original vector:\n";

  std::copy(
    numbers.begin(),
    numbers.end(),
    std::ostream_iterator<int>(fout, " ")
  );

  fout << "\n\n";

  auto minmax = std::minmax_element(numbers.begin(), numbers.end());

  fout << "Minimum element: " << *minmax.first << '\n';
  fout << "Maximum element: " << *minmax.second << "\n\n";

  std::sort(numbers.begin(), numbers.end());

  fout << "Sorted vector:\n";

  std::copy(
    numbers.begin(),
    numbers.end(),
    std::ostream_iterator<int>(fout, " ")
  );

  fout << "\n\n";

  int positiveCount = std::count_if(
    numbers.begin(),
    numbers.end(),
    [](int value) {
      return value > 0;
    }
  );

  int negativeCount = std::count_if(
    numbers.begin(),
    numbers.end(),
    [](int value) {
      return value < 0;
    }
  );

  int zeroCount = std::count(
    numbers.begin(),
    numbers.end(),
    0
  );

  fout << "Positive elements: " << positiveCount << '\n';
  fout << "Negative elements: " << negativeCount << '\n';
  fout << "Zero elements: " << zeroCount << "\n\n";

  double average = static_cast<double>(
                     std::accumulate(numbers.begin(), numbers.end(), 0)
                   ) / numbers.size();

  fout << "Average value: " << average << "\n\n";

  numbers.erase(
    std::remove_if(
      numbers.begin(),
      numbers.end(),
      [average](int value) {
        return value < average;
      }
    ),
    numbers.end()
  );

  fout << "vector after removing elements smaller than average:\n";

  std::copy(
    numbers.begin(),
    numbers.end(),
    std::ostream_iterator<int>(fout, " ")
  );

  fout << "\n\n";
  
  std::sort(numbers.begin(), numbers.end());

  std::vector<int> uniqueNumbers = numbers;

  uniqueNumbers.erase(
    std::unique(uniqueNumbers.begin(), uniqueNumbers.end()),
    uniqueNumbers.end()
  );

  fout << "Unique sorted vector:\n";

  std::copy(
    uniqueNumbers.begin(),
    uniqueNumbers.end(),
    std::ostream_iterator<int>(fout, " ")
  );

  fout << '\n';

  fout.close();

  std::cout << "Results saved to output.txt\n";

  return 0;
}
