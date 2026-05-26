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

  int Length = 0;
  std::cout << "Length: ";
  std::cin >> Length;
  std::string Word;
  std::cout << "Word: ";
  std::cin >> Word;

  lines.erase(std::remove_if(lines.begin(), lines.end(),
                             [Length](const std::string &s) { return static_cast<int>(s.size()) < Length; }),
              lines.end());

  const std::vector<std::string> filtered = lines;

  const std::string vowels_to_remove = "aeiouyAEIOUY";
  std::for_each(lines.begin(), lines.end(), [&vowels_to_remove](std::string &s) {
    s.erase(std::remove_if(s.begin(), s.end(), [&vowels_to_remove](char c) { return vowels_to_remove.find(c) != std::string::npos; }),
            s.end());
  });

  const auto found = std::find_if(original.begin(), original.end(), [&Word](const std::string &s) {
    return s.find(Word) != std::string::npos;
  });

  const int total_chars = std::accumulate(
      lines.begin(), lines.end(), 0, [](int sum, const std::string &s) { return sum + static_cast<int>(s.size()); });

  std::vector<int> lengths;
  std::transform(lines.begin(), lines.end(), std::back_inserter(lengths),
                 [](const std::string &s) { return static_cast<int>(s.size()); });

  std::ofstream out("output.txt");

  out << "Original:" << std::endl;
  std::copy(original.begin(), original.end(), std::ostream_iterator<std::string>(out, "\n"));
  out << std::endl << "After deleting shorter than length " << Length << ": " << std::endl;
  std::copy(filtered.begin(), filtered.end(), std::ostream_iterator<std::string>(out, "\n"));
  out << std::endl << "After deleting 'aeiouy': " << std::endl;
  std::copy(lines.begin(), lines.end(), std::ostream_iterator<std::string>(out, "\n"));
  out << std::endl << "Search for word, " << (found != lines.end() ? "found: " + *found : "not found") << std::endl;
  out << "Total char count: " << total_chars << std::endl;
  out << "Lengths: " << std::endl;
  std::copy(lengths.begin(), lengths.end(), std::ostream_iterator<int>(out, "\n"));

  out.close();
}