#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ifstream input("input.txt");
  if (!input) {
    std::cerr << "Failed to open input.txt\n";
    return 1;
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(input, line)) {
    lines.push_back(line);
  }
  input.close();

  std::vector<std::string> original = lines;

  size_t threshold;
  std::string search_word;

  std::cout << "Enter length threshold: ";
  std::cin >> threshold;
  std::cout << "Enter word to search: ";
  std::cin >> search_word;

  auto remove_short = [threshold](std::vector<std::string>& vec) {
    vec.erase(std::remove_if(vec.begin(), vec.end(),
                             [threshold](const std::string& s) {
                               return s.length() < threshold;
                             }),
              vec.end());
  };
  remove_short(lines);

  std::vector<std::string> replaced = lines;
  std::for_each(replaced.begin(), replaced.end(), [](std::string& s) {
    std::replace(s.begin(), s.end(), ' ', '_');
  });

  std::string found_line = "Not found";
  auto find_word = [&search_word,
                    &found_line](const std::vector<std::string>& vec) {
    auto it = std::find_if(vec.begin(), vec.end(),
                           [&search_word](const std::string& s) {
                             return s.find(search_word) != std::string::npos;
                           });
    if (it != vec.end()) {
      found_line = *it;
    }
  };
  find_word(replaced);

  size_t total_no_underscore = 0;
  for (const auto& s : replaced) {
    for (char c : s) {
      if (c != '_') total_no_underscore++;
    }
  }

  std::vector<int> lengths;
  std::transform(
      replaced.begin(), replaced.end(), std::back_inserter(lengths),
      [](const std::string& s) { return static_cast<int>(s.length()); });

  std::ofstream output("output.txt");
  if (!output) {
    std::cerr << "Failed to create output.txt\n";
    return 1;
  }

  output << "Original vector:\n";
  for (const auto& s : original) output << s << "\n";
  output << "\n";

  output << "After removing strings shorter than " << threshold << ":\n";
  for (const auto& s : lines) output << s << "\n";
  output << "\n";

  output << "After replacing spaces with '_':\n";
  for (const auto& s : replaced) output << s << "\n";
  output << "\n";

  output << "Search result for \"" << search_word << "\": " << found_line
         << "\n\n";

  output << "Total characters without '_': " << total_no_underscore << "\n\n";

  output << "Vector of line lengths: ";
  for (int len : lengths) output << len << " ";
  output << "\n";

  output.close();
  std::cout << "Done. Check output.txt\n";

  return 0;
}
