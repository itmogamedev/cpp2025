#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-50, 100);

  std::vector<int> v(20);
  std::generate(v.begin(), v.end(), [&]() { return dist(gen); });

  std::ofstream out("output.txt");
  if (!out) {
    std::cerr << "Cannot open output.txt" << std::endl;
    return 1;
  }

  auto [minIt, maxIt] = std::minmax_element(v.begin(), v.end());
  out << "Min: " << *minIt << ", Max: " << *maxIt << "\n";

  std::vector<int> sorted_v = v;
  std::sort(sorted_v.begin(), sorted_v.end());
  out << "Sorted vector: ";
  std::copy(sorted_v.begin(), sorted_v.end(),
            std::ostream_iterator<int>(out, " "));
  out << "\n";

  int positive = std::count_if(v.begin(), v.end(), [](int x) { return x > 0; });
  int negative = std::count_if(v.begin(), v.end(), [](int x) { return x < 0; });
  int zero = std::count_if(v.begin(), v.end(), [](int x) { return x == 0; });
  out << "Positive: " << positive << " Negative: " << negative
      << " Zero: " << zero << "\n";

  double avg = std::accumulate(v.begin(), v.end(), 0.0) / v.size();
  out << "Average: " << avg << "\n";

  std::vector<int> v_filtered = v;
  auto new_end = std::remove_if(v_filtered.begin(), v_filtered.end(),
                                [avg](int x) { return x < avg; });
  v_filtered.erase(new_end, v_filtered.end());
  out << "After removing elements < average: ";
  std::copy(v_filtered.begin(), v_filtered.end(),
            std::ostream_iterator<int>(out, " "));
  out << "\n";

  std::sort(v_filtered.begin(), v_filtered.end());
  std::vector<int> v_unique;
  std::unique_copy(v_filtered.begin(), v_filtered.end(),
                   std::back_inserter(v_unique));
  out << "modified sorted vector: ";
  std::copy(v_unique.begin(), v_unique.end(),
            std::ostream_iterator<int>(out, " "));
  out << "\n";
  out << "\n" << "________0000_____________________777______________\n"
        "______0000______________________77777_____________\n"
        "____00000______________________7777777____________\n"
        "___00000______________________777777777___________\n"
        "__000000____________77777777777777777777777777777_\n"
        "_0000000______________7777777777777777777777777___\n"
        "_0000000_______________7777777777777777777777_____\n"
        "_0000__00_________________77777777777777777_______\n"
        "_0000__00000000__________777777777_777777777______\n"
        "_000000000000___________7777777_______7777777_____\n"
        "__0000000000___________77777_____________77777____\n"
        "___0000_000000________777___________________777___\n"
        "____00000_______0___________0000__________________\n"
        "______000000__00000______000000___________________\n"
        "________000000000000000000000_____________________\n"
        "__________00000000000000000_______________________\n"
        "______________000000000___________________________";
  out.close();
  return 0;
}