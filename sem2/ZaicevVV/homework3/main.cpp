#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

namespace {

void PrintStringVector(const std::vector<std::string>& lines,
                       std::ofstream& output) {
  if (lines.empty()) {
    output << "(empty)\n";
    return;
  }

  for (const std::string& line : lines) {
    output << line << '\n';
  }
}

void PrintSizeVector(const std::vector<int>& values, std::ofstream& output) {
  if (values.empty()) {
    output << "(empty)\n";
    return;
  }

  for (std::size_t i = 0; i < values.size(); ++i) {
    if (i > 0) {
      output << ' ';
    }
    output << values[i];
  }
  output << '\n';
}

}  // namespace

int main() {
  std::ifstream input("input.txt");
  std::ofstream output("output.txt");

  if (!input.is_open()) {
    std::cerr << "Failed to open input.txt\n";
    return 1;
  }

  if (!output.is_open()) {
    std::cerr << "Failed to open output.txt\n";
    return 1;
  }

  std::vector<std::string> original_lines;
  std::string line;
  while (std::getline(input, line)) {
    original_lines.push_back(line);
  }

  int min_length = 0;
  std::string search_word;

  std::cout << "Enter minimum line length: ";
  std::cin >> min_length;
  std::cout << "Enter search word: ";
  std::cin >> search_word;

  std::vector<std::string> filtered_lines = original_lines;

  const auto is_shorter_than_min_length =
      [min_length](const std::string& current_line) {
        return static_cast<int>(current_line.length()) < min_length;
      };

  filtered_lines.erase(
      std::remove_if(filtered_lines.begin(), filtered_lines.end(),
                     is_shorter_than_min_length),
      filtered_lines.end());

  std::vector<std::string> processed_lines = filtered_lines;

  std::for_each(processed_lines.begin(), processed_lines.end(),
                [](std::string& current_line) {
                  std::replace(current_line.begin(), current_line.end(), ' ',
                               '_');
                });

  const auto found_it =
      std::find_if(processed_lines.begin(), processed_lines.end(),
                   [&search_word](const std::string& current_line) {
                     return current_line.find(search_word) != std::string::npos;
                   });

  const int total_chars_without_underscores = std::accumulate(
      processed_lines.begin(), processed_lines.end(), 0,
      [](int sum, const std::string& current_line) {
        const int underscores = static_cast<int>(
            std::count(current_line.begin(), current_line.end(), '_'));
        return sum + static_cast<int>(current_line.length()) - underscores;
      });

  std::vector<int> line_lengths;
  line_lengths.reserve(processed_lines.size());
  std::transform(processed_lines.begin(), processed_lines.end(),
                 std::back_inserter(line_lengths),
                 [](const std::string& current_line) {
                   return static_cast<int>(current_line.length());
                 });

  output << "Original vector of strings:\n";
  PrintStringVector(original_lines, output);

  output << "\nVector after removing short strings:\n";
  PrintStringVector(filtered_lines, output);

  output << "\nVector after replacing spaces with underscores:\n";
  PrintStringVector(processed_lines, output);

  output << "\nSearch result for word \"" << search_word << "\":\n";
  if (found_it != processed_lines.end()) {
    output << *found_it << '\n';
  } else {
    output << "Not found\n";
  }

  output << "\nTotal number of characters without underscores:\n";
  output << total_chars_without_underscores << '\n';

  output << "\nVector of string lengths:\n";
  PrintSizeVector(line_lengths, output);

  return 0;
}
