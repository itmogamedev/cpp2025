#include<iostream>
#include<stdexcept>
#include<climits>
#include<set>

const static unsigned long long kOverflowEdge = (ULLONG_MAX / 3 - 3);

bool testCollatzConjecture(unsigned long long n) {
  std::set<unsigned long long> visited_numbers;

  while (n != 1) {
    visited_numbers.insert(n);
    if (n % 2) {
      if (n > kOverflowEdge)
        throw std::overflow_error("n reaches ULLONG_MAX before reaching 1");
      n = (3 * n + 1);
    } else n /= 2;
    if (visited_numbers.contains(n)) return false;
  }

  return true;
}

int main() {
  unsigned long long n;
  std::cin >> n;
  std::cout << "The hypothesis is "
    << (testCollatzConjecture(n) ? "" : "not ")
    << "true for " << n << std::endl;
}