#include "file_processor.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>

const std::string FileProcessor::kInputFile = "input.txt";
const std::string FileProcessor::kOutputFile = "output.txt";
const char FileProcessor::kUnderscore = '_';

void FileProcessor::run() {
  int threshold = 0;
  std::string search_word;

  std::cout << "Enter length threshold: ";
  std::cin >> threshold;
  std::cin.ignore();
  std::cout << "Enter search word: ";
  std::getline(std::cin, search_word);

  process(threshold, search_word);
}

void FileProcessor::readInputFile(const std::string& filename) {
  std::ifstream in(filename);
  if (!in) {
    std::cerr << "Cannot open input file: " << filename << std::endl;
    return;
  }
  std::string line;
  while (std::getline(in, line)) {
    original_lines.push_back(line);
  }
}

void FileProcessor::process(int threshold, const std::string& search_word) {
  readInputFile(kInputFile);
  if (original_lines.empty()) {
    std::cerr << "No data read from file." << std::endl;
    return;
  }

  after_remove = original_lines;
  auto new_end =
      std::remove_if(after_remove.begin(), after_remove.end(),
                     [threshold](const std::string& s) {
                       return s.length() < static_cast<std::size_t>(threshold);
                     });
  after_remove.erase(new_end, after_remove.end());

  after_replace = after_remove;
  std::for_each(after_replace.begin(), after_replace.end(), [](std::string& s) {
    std::replace(s.begin(), s.end(), ' ', kUnderscore);
  });

  auto it = std::find_if(after_replace.begin(), after_replace.end(),
                         [&search_word](const std::string& s) {
                           return s.find(search_word) != std::string::npos;
                         });
  word_found = (it != after_replace.end());

  total_chars_no_underscore = std::accumulate(
      after_replace.begin(), after_replace.end(), 0,
      [](int sum, const std::string& s) {
        return sum + std::count_if(s.begin(), s.end(),
                                   [](char c) { return c != kUnderscore; });
      });

  line_lengths.clear();
  std::transform(after_replace.begin(), after_replace.end(),
                 std::back_inserter(line_lengths), [](const std::string& s) {
                   return static_cast<int>(s.length());
                 });

  writeResults(kOutputFile);
}

void FileProcessor::writeResults(const std::string& filename) const {
  std::ofstream out(filename);
  if (!out) {
    std::cerr << "Cannot open output file." << std::endl;
    return;
  }

  auto print_vector = [&out](const std::string& caption,
                             const std::vector<std::string>& vec) {
    out << caption << ":\n";
    for (const auto& s : vec) {
      out << s << '\n';
    }
    out << '\n';
  };

  print_vector("Original lines", original_lines);

  print_vector("After removing short lines (threshold applied)", after_remove);

  print_vector("After replacing spaces with '_' (Variant 1)", after_replace);

  out << "Search result for word '" << (word_found ? "found" : "not found")
      << "'\n\n";

  out << "Total characters (excluding '_'): " << total_chars_no_underscore
      << "\n\n";

  out << "Line lengths:";
  for (const int len : line_lengths) {
    out << ' ' << len;
  }
  out << std::endl;
}
