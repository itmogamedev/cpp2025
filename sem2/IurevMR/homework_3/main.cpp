#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

std::vector<std::string> ReadLinesFromFile(const std::string& filename) {
  std::ifstream input(filename);
  std::vector<std::string> lines;
  std::string line;

  while (std::getline(input, line)) {
    lines.push_back(line);
  }

  return lines;
}

void PrintStringVector(std::ofstream& output,
                       const std::string& title,
                       const std::vector<std::string>& lines) {
  output << title << "\n";

  for (const auto& line : lines) {
    output << line << "\n";
  }

  output << "\n";
}

void PrintIntVector(std::ofstream& output,
                    const std::string& title,
                    const std::vector<int>& numbers) {
  output << title << "\n";

  for (int number : numbers) {
    output << number << " ";
  }

  output << "\n\n";
}

void RemoveShortLines(std::vector<std::string>& lines, std::size_t threshold) {
  lines.erase(
      std::remove_if(
          lines.begin(),
          lines.end(),
          [threshold](const std::string& line) {
            return line.length() < threshold;
          }),
      lines.end());
}

void ReplaceSpacesWithUnderscores(std::vector<std::string>& lines) {
  std::for_each(
      lines.begin(),
      lines.end(),
      [](std::string& line) {
        std::replace(line.begin(), line.end(), ' ', '_');
      });
}

std::string FindLineWithWord(const std::vector<std::string>& lines,
                             const std::string& word) {
  auto found = std::find_if(
      lines.begin(),
      lines.end(),
      [&word](const std::string& line) {
        return line.find(word) != std::string::npos;
      });

  if (found == lines.end()) {
    return "";
  }

  return *found;
}

std::size_t CountCharactersWithoutUnderscores(
    const std::vector<std::string>& lines) {
  return std::accumulate(
      lines.begin(),
      lines.end(),
      static_cast<std::size_t>(0),
      [](std::size_t sum, const std::string& line) {
        return sum + static_cast<std::size_t>(
            std::count_if(
                line.begin(),
                line.end(),
                [](char ch) {
                  return ch != '_';
                }));
      });
}

std::vector<int> GetLineLengths(const std::vector<std::string>& lines) {
  std::vector<int> lengths;

  std::transform(
      lines.begin(),
      lines.end(),
      std::back_inserter(lengths),
      [](const std::string& line) {
        return static_cast<int>(line.length());
      });

  return lengths;
}

int main() {
  std::ofstream output("output.txt");

  if (!output) {
    std::cerr << "Error: could not open output.txt\n";
    return 1;
  }

  std::ifstream check_input("input.txt");

  if (!check_input) {
    output << "Error: could not open input.txt\n";
    return 1;
  }

  check_input.close();

  std::size_t threshold;
  std::string search_word;

  std::cout << "Enter the minimum line length: ";
  std::cin >> threshold;

  std::cout << "Enter the word to search for: ";
  std::cin >> search_word;

  if (!std::cin) {
    output << "Error: invalid input\n";
    return 1;
  }

  std::vector<std::string> lines = ReadLinesFromFile("input.txt");
  std::vector<std::string> original_lines = lines;

  PrintStringVector(output, "Original vector of strings:", original_lines);

  RemoveShortLines(lines, threshold);

  PrintStringVector(
      output,
      "Vector of strings after removing short lines:",
      lines);

  ReplaceSpacesWithUnderscores(lines);

  PrintStringVector(
      output,
      "Vector of strings after replacing spaces with underscores:",
      lines);

  std::string found_line = FindLineWithWord(lines, search_word);

  output << "Search result for the word \"" << search_word << "\":\n";

  if (!found_line.empty()) {
    output << "Found line: " << found_line << "\n\n";
  } else {
    output << "No line containing the given word was found\n\n";
  }

  std::size_t total_characters = CountCharactersWithoutUnderscores(lines);

  output << "Total number of characters without underscores:\n";
  output << total_characters << "\n\n";

  std::vector<int> lengths = GetLineLengths(lines);

  PrintIntVector(output, "Vector of line lengths:", lengths);

  return 0;
}
