
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

int main() {
  std::ofstream out("output.txt");
  std::vector<int> random_ints(20);

  auto Title = [&out](std::string title) {
    out << "\n=====" + title + "=====\n";
  };

  std::mt19937 random(std::time(0));
  std::uniform_int_distribution<int> dist(-50, 100);

  std::generate(random_ints.begin(), random_ints.end(),
                [&]() { return dist(random); });

  Title("Min value");
  out << *std::min_element(random_ints.begin(), random_ints.end()) << '\n';

  Title("Max value");
  out << *std::max_element(random_ints.begin(), random_ints.end()) << '\n';

  Title("Sorted");
  std::sort(random_ints.begin(), random_ints.end(),
            [](int a, int b) { return a < b; });

  std::for_each(random_ints.begin(), random_ints.end(),
                [&out](int a) { out << a << ' '; });
  out << '\n';

  Title("Less Null Greater");
  int less = 0, null = 0, greater = 0;
  std::for_each(random_ints.begin(), random_ints.end(),
                [&less, &null, &greater](int i) {
                  if (i < 0) {
                    ++less;
                    return;
                  } else if (less > 0) {
                    ++greater;
                    return;
                  } else {
                    ++null;
                    return;
                  }
                });
  out << less << ' ' << null << ' ' << greater << '\n';

  Title("Middle arifm");
  out << static_cast<float>(
             std::accumulate(random_ints.begin(), random_ints.end(), 0)) /
             random_ints.size()
      << '\n';

  Title("Without even");
  random_ints.erase(std::remove_if(random_ints.begin(), random_ints.end(),
                                   [](int a) { return a % 2 == 0; }),
                    random_ints.end());
  std::for_each(random_ints.begin(), random_ints.end(),
                [&out](int a) { out << a << ' '; });
  out << '\n';

  Title("Without doubles");
  random_ints.erase(std::unique(random_ints.begin(), random_ints.end()),
                    random_ints.end());
  std::for_each(random_ints.begin(), random_ints.end(),
                [&out](int a) { out << a << ' '; });
  out << '\n';

  return 0;
}
