#include "stringProcessor.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>

void StringProcessor::readInput(const std::string& filename) {
  std::ifstream input(filename);
  if (!input) {
    throw std::runtime_error("Cannot open input file: " + filename);
  }
  std::string line;
  while (std::getline(input, line)) {
    original_lines.push_back(line);
  }
  lines_after_short = original_lines;
  lines_after_vowels = original_lines;
}

void StringProcessor::removeShortStrings(int threshold) {
  lines_after_short.erase(
      std::remove_if(lines_after_short.begin(), lines_after_short.end(),
                     [threshold](const std::string& s) {
                       return s.length() < static_cast<size_t>(threshold);
                     }),
      lines_after_short.end());
  lines_after_vowels = lines_after_short;
}

void StringProcessor::removeVowels() {
  auto isVowel = [](char c) {
    c = std::tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
  };
  for (auto& str : lines_after_vowels) {
    str.erase(std::remove_if(str.begin(), str.end(), isVowel), str.end());
  }
}

std::string StringProcessor::searchWord(const std::string& word) const {
  auto it = std::find_if(lines_after_short.begin(), lines_after_short.end(),
                         [&word](const std::string& s) {
                           return s.find(word) != std::string::npos;
                         });
  return (it != lines_after_short.end()) ? *it : "";
}

int StringProcessor::countCharsWithoutUnderscores() const {
  int total = 0;
  std::for_each(original_lines.begin(), original_lines.end(),
                [&total](const std::string& s) {
                  for (char c : s) {
                    if (c != '_') {
                      ++total;
                    }
                  }
                });
  return total;
}

std::vector<int> StringProcessor::getLengths() const {
  std::vector<int> lengths;
  lengths.reserve(original_lines.size());
  std::transform(
      original_lines.begin(), original_lines.end(), std::back_inserter(lengths),
      [](const std::string& s) { return static_cast<int>(s.length()); });
  return lengths;
}

void StringProcessor::outputResults(const std::string& filename,
                                    const std::string& foundLine,
                                    int totalChars,
                                    const std::vector<int>& lengths) const {
  std::ofstream output(filename);
  if (!output) {
    throw std::runtime_error("Cannot open output file: " + filename);
  }

  auto outputStrings = [&output](const std::vector<std::string>& vec) {
    for (const auto& s : vec) {
      output << s << '\n';
    }
  };

  output << "Исходный вектор строк:\n";
  outputStrings(original_lines);

  output << "\nВектор строк после удаления коротких строк:\n";
  outputStrings(lines_after_short);

  output << "\nВектор строк после удаления гласных букв:\n";
  outputStrings(lines_after_vowels);

  output << "\nРезультат поиска заданного слова:\n";
  if (!foundLine.empty()) {
    output << foundLine << '\n';
  } else {
    output << "Строка не найдена\n";
  }

  output << "\nОбщее количество символов без \"_\":\n";
  output << totalChars << '\n';

  output << "\nВектор длин строк:\n";
  for (size_t i = 0; i < lengths.size(); ++i) {
    if (i > 0) output << ' ';
    output << lengths[i];
  }
  output << '\n';
}
