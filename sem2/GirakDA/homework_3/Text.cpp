#include "Text.h"

#include <algorithm>
#include <fstream>
#include <iostream>

bool TextProcessor::loadFromFile(const std::string& filename) {
  std::ifstream in_file(filename);
  original_lines.clear();
  current_lines.clear();
  std::string line;
  while (std::getline(in_file, line)) {
    original_lines.push_back(line);
    current_lines.push_back(line);
  }

  lengths.clear();
  std::transform(
      original_lines.begin(), original_lines.end(), std::back_inserter(lengths),
      [](const std::string& s) { return static_cast<int>(s.length()); });

  return !original_lines.empty();
}

void TextProcessor::removeShortLines(int threshold) {
  current_lines.erase(std::remove_if(current_lines.begin(), current_lines.end(),
                                     [threshold](const std::string& s) {
                                       return s.length() < threshold;
                                     }),
                      current_lines.end());
}

void TextProcessor::replaceSpacesWithUnderscore() {
  std::transform(current_lines.begin(), current_lines.end(),
                 current_lines.begin(), [](std::string s) {
                   std::replace(s.begin(), s.end(), ' ', '_');
                   return s;
                 });
}

std::string TextProcessor::findLineWithWord(const std::string& word) const {
  auto it = std::find_if(original_lines.begin(), original_lines.end(),
                         [&word](const std::string& s) {
                           return s.find(word) != std::string::npos;
                         });

  if (it != original_lines.end()) {
    return "Found: \"" + *it + "\"";
  }
  return "Word \"" + word + "\" not found";
}

int TextProcessor::countCharsWithoutUnderscore() const {
  int total = 0;
  for (const auto& s : current_lines) {
    for (char c : s) {
      if (c != '_') total++;
    }
  }
  return total;
}

void TextProcessor::saveToFile(const std::string& filename, int threshold,
                               const std::string& search_word) const {
  std::ofstream out_file(filename);

  out_file << "         THE ORIGINAL ROW VECTOR         \n";
  for (size_t i = 0; i < original_lines.size(); ++i) {
    out_file << i + 1 << ". \"" << original_lines[i] << "\"\n";
  }

  out_file << "\n         AFTER REMOVING SHORT LINES (length >= " << threshold
           << ")         \n";
  std::vector<std::string> after_removal = current_lines;
  for (auto& s : after_removal) {
    std::replace(s.begin(), s.end(), '_', ' ');
  }

  if (after_removal.empty()) {
    out_file << "(empty)\n";
  } else {
    for (size_t i = 0; i < after_removal.size(); ++i) {
      out_file << i + 1 << ". \"" << after_removal[i] << "\"\n";
    }
  }

  out_file << "\n         AFTER REPLACING SPACES WITH '_'         \n";
  for (size_t i = 0; i < current_lines.size(); ++i) {
    out_file << i + 1 << ". \"" << current_lines[i] << "\"\n";
  }

  out_file << "\n         SEARCH RESULT         \n";
  out_file << findLineWithWord(search_word) << "\n";

  out_file << "\n         TOTAL NUMBER OF SYMBOLS (without '_')         \n";
  out_file << countCharsWithoutUnderscore() << "\n";

  out_file << "\n         VECTOR OF LINE LENGTHS         \n";
  for (size_t i = 0; i < lengths.size(); ++i) {
    out_file << i + 1 << ". " << lengths[i] << " symbols -> \""
             << original_lines[i] << "\"\n";
  }
}
void work() {
  TextProcessor p;
  int t;
  std::string w;
  p.loadFromFile("input.txt");
  std::cout << "Threshold: ";
  std::cin >> t;
  p.removeShortLines(t);
  p.replaceSpacesWithUnderscore();
  std::cout << "Word: ";
  std::cin >> w;
  p.saveToFile("output.txt", t, w);
}
