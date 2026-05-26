#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

struct Line {
  std::string data;
  operator std::string() const { return data; }
  friend std::istream &operator>>(std::istream &is, Line &l) {
    std::getline(is, l.data);
    if (!l.data.empty() && l.data.back() == '\r')
      l.data.pop_back();
    return is;
  }
};

int main() {
  std::ifstream in("input.txt");

  std::vector<std::string> lines(std::istream_iterator<Line>(in), std::istream_iterator<Line>{});
  in.close();

  const std::vector<std::string> original = lines;

  int threshold = 0;
  std::cout << "threshold: ";
  std::cin >> threshold;

  std::string search_word;
  std::cout << "search word: ";
  std::cin >> search_word;

  lines.erase(std::remove_if(lines.begin(), lines.end(),
                             [threshold](const std::string &s) { return static_cast<int>(s.size()) < threshold; }),
              lines.end());

  const std::vector<std::string> filtered = lines;

  const std::string vowels = "aeiouyAEIOUY";
  std::for_each(lines.begin(), lines.end(), [&vowels](std::string &s) {
    s.erase(std::remove_if(s.begin(), s.end(), [&vowels](char c) { return vowels.find(c) != std::string::npos; }),
            s.end());
  });

  const auto found = std::find_if(original.begin(), original.end(), [&search_word](const std::string &s) {
    return s.find(search_word) != std::string::npos;
  });

  const int total_chars = std::accumulate(
      lines.begin(), lines.end(), 0, [](int sum, const std::string &s) { return sum + static_cast<int>(s.size()); });

  std::vector<int> lengths;
  std::transform(lines.begin(), lines.end(), std::back_inserter(lengths),
                 [](const std::string &s) { return static_cast<int>(s.size()); });

  std::ofstream out("output.txt");

  out << "initial:" << std::endl;
  std::copy(original.begin(), original.end(), std::ostream_iterator<std::string>(out, "\n"));

  out << std::endl << "after deleting below threshold " << threshold << ": " << std::endl;
  std::copy(filtered.begin(), filtered.end(), std::ostream_iterator<std::string>(out, "\n"));

  out << std::endl << "after deleting vowels: " << std::endl;
  std::copy(lines.begin(), lines.end(), std::ostream_iterator<std::string>(out, "\n"));

  out << std::endl << "search for word, " << (found != lines.end() ? "found: " + *found : "not found") << std::endl;

  out << "total char count: " << total_chars << std::endl;

  out << "lengths: " << std::endl;
  std::copy(lengths.begin(), lengths.end(), std::ostream_iterator<int>(out, "\n"));

  out.close();
}
