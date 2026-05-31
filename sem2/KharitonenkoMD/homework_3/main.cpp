#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void printVector(std::ofstream& out, const std::string& title,
                 const std::vector<std::string>& v) {
  out << title << "\n";
  std::for_each(v.begin(), v.end(),
                [&out](const std::string& s) { out << "  \"" << s << "\"\n"; });
  out << "\n";
}

int main() {
  std::ifstream inFile("input.txt");
  if (!inFile.is_open()) {
    std::cerr << "Could not open input.txt\n";
    return 1;
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(inFile, line)) {
    lines.push_back(line);
  }
  inFile.close();

  int threshold;
  std::cout << "Enter minimum line length (threshold): ";
  std::cin >> threshold;
  std::cin.ignore();

  std::string searchWord;
  std::cout << "Enter word to search for: ";
  std::getline(std::cin, searchWord);

  std::ofstream out("output.txt");
  if (!out.is_open()) {
    std::cerr << "Could not open output.txt\n";
    return 1;
  }

  printVector(out, "Original vector of strings", lines);

  lines.erase(std::remove_if(lines.begin(), lines.end(),
                             [threshold](const std::string& s) {
                               return static_cast<int>(s.size()) < threshold;
                             }),
              lines.end());

  printVector(out,
              "After removing lines shorter than " + std::to_string(threshold) +
                  " characters",
              lines);

  auto isVowel = [](char c) {
    char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' ||
           lower == 'u' || lower == 'y';
  };

  std::for_each(lines.begin(), lines.end(), [&isVowel](std::string& s) {
    s.erase(std::remove_if(s.begin(), s.end(), isVowel), s.end());
  });

  printVector(out, "After removing vowels (a, e, i, o, u, y)  ", lines);

  auto it = std::find_if(lines.begin(), lines.end(),
                         [&searchWord](const std::string& s) {
                           return s.find(searchWord) != std::string::npos;
                         });

  out << "  Search for word \"" << searchWord << "\"  \n";
  if (it != lines.end()) {
    out << "  Found in line: \"" << *it << "\"\n";
  } else {
    out << "  Word not found.\n";
  }
  out << "\n";

  int totalChars = std::accumulate(
      lines.begin(), lines.end(), 0, [](int sum, const std::string& s) {
        return sum + static_cast<int>(std::count_if(
                         s.begin(), s.end(), [](char c) { return c != '_'; }));
      });

  out << "  Total character count (excluding '_')  \n";
  out << "  " << totalChars << "\n\n";

  std::vector<int> lengths;
  lengths.reserve(lines.size());
  std::transform(
      lines.begin(), lines.end(), std::back_inserter(lengths),
      [](const std::string& s) { return static_cast<int>(s.size()); });

  out << "  Vector of string lengths  \n  ";
  std::for_each(lengths.begin(), lengths.end(),
                [&out](int len) { out << len << " "; });
  out << "\n";

  out.close();
  std::cout << "Results are in output.txt\n";
  return 0;
}
