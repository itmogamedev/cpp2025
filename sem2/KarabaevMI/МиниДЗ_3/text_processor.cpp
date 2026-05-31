#include "text_processor.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>

TextProcessor::TextProcessor(const std::string& input_path,
                             const std::string& output_path)
    : input_path(input_path),
      output_path(output_path),
      word_found(false),
      total_chars(0) {}

void TextProcessor::run() {
  readLines();
  std::size_t threshold = promptThreshold();
  std::string word = promptSearchWord();

  filtered_lines = original_lines;
  removeShortLines(threshold);

  transformed_lines = filtered_lines;
  replaceSpaces();

  searchLineWith(word);
  countCharsExcludingUnderscore();
  computeLineLengths();

  writeReport(threshold, word);
  std::cout << "Done. See " << output_path << '\n';
}

void TextProcessor::readLines() {
  std::ifstream in(input_path);
  std::string line;
  while (std::getline(in, line)) {
    original_lines.push_back(line);
  }
}

std::size_t TextProcessor::promptThreshold() const {
  std::size_t threshold = 0;
  std::cout << "Enter min line length threshold: ";
  std::cin >> threshold;
  return threshold;
}

std::string TextProcessor::promptSearchWord() const {
  std::string word;
  std::cout << "Enter word to search: ";
  std::cin >> word;
  return word;
}

void TextProcessor::removeShortLines(std::size_t threshold) {
  filtered_lines.erase(
      std::remove_if(filtered_lines.begin(), filtered_lines.end(),
                     [threshold](const std::string& s) {
                       return s.length() < threshold;
                     }),
      filtered_lines.end());
}

void TextProcessor::replaceSpaces() {
  std::for_each(transformed_lines.begin(), transformed_lines.end(),
                [](std::string& s) {
                  std::replace(s.begin(), s.end(), ' ', '_');
                });
}

void TextProcessor::searchLineWith(const std::string& word) {
  auto it = std::find_if(transformed_lines.begin(), transformed_lines.end(),
                         [&word](const std::string& s) {
                           return s.find(word) != std::string::npos;
                         });
  if (it != transformed_lines.end()) {
    word_found = true;
    found_line = *it;
  } else {
    word_found = false;
    found_line.clear();
  }
}

void TextProcessor::countCharsExcludingUnderscore() {
  total_chars = std::accumulate(
      transformed_lines.begin(), transformed_lines.end(), std::size_t{0},
      [](std::size_t acc, const std::string& s) {
        return acc + static_cast<std::size_t>(std::count_if(
                         s.begin(), s.end(), [](char c) { return c != '_'; }));
      });
}

void TextProcessor::computeLineLengths() {
  line_lengths.clear();
  std::transform(
      transformed_lines.begin(), transformed_lines.end(),
      std::back_inserter(line_lengths),
      [](const std::string& s) { return static_cast<int>(s.length()); });
}

void TextProcessor::writeReport(std::size_t threshold,
                                const std::string& word) const {
  std::ofstream out(output_path);

  auto print_vec = [&out](const std::vector<std::string>& v) {
    for (const auto& s : v) {
      out << "  " << s << '\n';
    }
  };

  out << "=== Original lines ===\n";
  print_vec(original_lines);

  out << "\n=== After removing lines shorter than " << threshold << " ===\n";
  print_vec(filtered_lines);

  out << "\n=== After replacing spaces with '_' ===\n";
  print_vec(transformed_lines);

  out << "\n=== Search for word \"" << word << "\" ===\n";
  if (word_found) {
    out << "  Found in line: " << found_line << '\n';
  } else {
    out << "  Not found\n";
  }

  out << "\n=== Total characters (excluding '_') ===\n";
  out << "  " << total_chars << '\n';

  out << "\n=== Line lengths ===\n  [";
  for (std::size_t i = 0; i < line_lengths.size(); ++i) {
    out << line_lengths[i];
    if (i + 1 < line_lengths.size()) {
      out << ", ";
    }
  }
  out << "]\n";
}
