#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <vector>

const int kVectorSise = 20;
const int kNumbersInf = -50;
const int kNumbersSup = 100;

int main() {
  int positive = 0;
  int negative = 0;
  float sum = 0.0;
  std::set<int> unique_set;
  std::vector<int> numbers(kVectorSise);
  std::random_device rd; 
  std::mt19937 engine(rd());
  std::uniform_int_distribution<int> dist(kNumbersInf, kNumbersSup);
  std::generate(numbers.begin(), numbers.end(), [&]() { return dist(engine); });

  std::ofstream file_out("output.txt");
  if (!file_out.is_open()) {
    std::cerr << "Unable to open outpun.txt file" << std::endl;
    return EXIT_FAILURE;
  }

  std::sort(numbers.begin(), numbers.end());

  file_out << numbers[0] << ' ' << numbers[kVectorSise - 1] << "\n\n";
  auto f_cout = [&file_out]<typename T>(T& n) mutable { file_out << n << ' '; };
  std::for_each(numbers.begin(), numbers.end(), f_cout);
  file_out << "\n\n";

  std::for_each(numbers.begin(), numbers.end(),
                [&positive, &negative, &sum](int n) mutable {
                  if (n > 0)
                    ++positive;
                  else if (n < 0)
                    ++negative;
                  sum += n;
                });

  float average = sum / kVectorSise;

  numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                               [&average](int n) { return n < average; }), numbers.end());

  file_out << negative << ' ' << (kVectorSise - positive - negative) << ' '
           << positive << "\n\n";
  file_out << average << "\n\n";
  std::for_each(numbers.begin(), numbers.end(), f_cout);
  file_out << "\n\n";

  std::for_each(numbers.begin(), numbers.end(),
                [&unique_set](int n) mutable { unique_set.insert(n); });

  std::for_each(unique_set.begin(), unique_set.end(), f_cout);
  file_out << "\n\n";
  file_out.close();
}
