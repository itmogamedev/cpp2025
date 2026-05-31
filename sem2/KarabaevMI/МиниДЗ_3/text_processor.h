#pragma once

#include <cstddef>
#include <string>
#include <vector>

class TextProcessor {
 public:
  TextProcessor(const std::string& input_path, const std::string& output_path);

  void run();

 private:
  std::string input_path;
  std::string output_path;
  std::vector<std::string> original_lines;
  std::vector<std::string> filtered_lines;
  std::vector<std::string> transformed_lines;
  std::string found_line;
  bool word_found;
  std::size_t total_chars;
  std::vector<int> line_lengths;

  void readLines();
  std::size_t promptThreshold() const;
  std::string promptSearchWord() const;

  void removeShortLines(std::size_t threshold);
  void replaceSpaces();
  void searchLineWith(const std::string& word);
  void countCharsExcludingUnderscore();
  void computeLineLengths();

  void writeReport(std::size_t threshold, const std::string& word) const;
};
