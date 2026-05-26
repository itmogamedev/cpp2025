// VARIANT: 1
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <string>
#include <vector>

void init() {
  std::ofstream file("output.txt");
  if (!file.is_open()) {
    std::cout << "Failed open file" << std::endl;
  }

  file.clear();
  file.close();
}

void output(std::string data) {
  std::ofstream file("output.txt", std::ios::app);
  if (!file.is_open()) {
    std::cout << "Failed open file" << std::endl;
  }

  file << data << '\n';
  file.close();
}

int main() {
  init();
  std::string str{};

  // GENERATION
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> distrib(-50, 100);
  std::vector<int> vec(20);
  std::generate(begin(vec), end(vec),
                [&distrib, &gen]() { return distrib(gen); });

  // MIN & MAX
  auto max = max_element(begin(vec), end(vec));
  auto min = min_element(begin(vec), end(vec));

  // OUTPUT MIN&MAX
  str = "Max: " + std::to_string(*max) + "; " + "Min: " + std::to_string(*min);
  output(str);

  // SORT
  std::sort(begin(vec), end(vec));

  // OUTPUT SORT
  str = "Sorted vector: ";
  std::for_each(begin(vec), end(vec),
                [&str](int elem) { str += std::to_string(elem) + " "; });
  output(str);

  // NEGATIVE, NEUTRAL, POSITIVE
  int neg{}, neutral{}, pos{};
  std::for_each(begin(vec), end(vec), [&neg, &neutral, &pos](int elem) {
    if (elem < 0)
      neg++;
    else if (elem == 0)
      neutral++;
    else
      pos++;
  });

  // OUTPUT NEGATIVE, NEUTRAL, POSITIVE
  str = "Neg: " + std::to_string(neg) + "; " +
        "Neutral: " + std::to_string(neutral) + "; " +
        "Pos: " + std::to_string(pos);
  output(str);

  // AVERAGE
  double avg{};
  avg =
      static_cast<float>(std::accumulate(begin(vec), end(vec), 0)) / vec.size();

  // OUTPUT AVERAGE
  str = "Average: " + std::to_string(avg);
  output(str);

  // ONLY ODD
  std::vector<int> only_odd;
  std::for_each(begin(vec), end(vec), [&only_odd](int elem) {
    if (elem % 2 != 0) only_odd.push_back(elem);
  });

  // OUTPUT ONLY ODD
  str = "Only odd numbers: ";
  std::for_each(begin(only_odd), end(only_odd),
                [&str](int elem) { str += std::to_string(elem) + " "; });
  output(str);

  // SORTED ONLY UNIQUE ODD
  std::set<int> set(begin(only_odd), end(only_odd));

  // OUTPUT ONLY UNIQUE ODD
  str = "Only unique odd numbers: ";
  std::for_each(begin(set), end(set),
                [&str](int elem) { str += std::to_string(elem) + " "; });
  output(str);

  return 0;
}
