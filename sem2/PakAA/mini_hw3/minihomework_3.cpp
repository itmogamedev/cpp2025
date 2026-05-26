#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

namespace {

std::vector<std::string> readLines(const std::string& path) {
  std::ifstream input(path);
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(input, line)) {
    lines.push_back(line);
  }
  return lines;
}

void writeStringVector(std::ofstream& out, const std::vector<std::string>& vec,
                       const std::string& title) {
  out << title << ":\n";
  if (vec.empty()) {
    out << "  (empty)\n";
  } else {
    for (const auto& s : vec) {
      out << "  " << s << "\n";
    }
  }
  out << "\n";
}

void writeIntVector(std::ofstream& out, const std::vector<int>& vec,
                    const std::string& title) {
  out << title << ":\n  [";
  for (std::size_t i = 0; i < vec.size(); ++i) {
    out << vec[i];
    if (i + 1 < vec.size()) {
      out << ", ";
    }
  }
  out << "]\n\n";
}

// Lambda with capture by VALUE: threshold is copied into the closure.
std::vector<std::string> filterShort(const std::vector<std::string>& src,
                                     int threshold) {
  std::vector<std::string> result = src;
  auto isTooShort = [threshold](const std::string& s) {
    return s.length() < static_cast<std::size_t>(threshold);
  };
  result.erase(std::remove_if(result.begin(), result.end(), isTooShort),
               result.end());
  return result;
}

// Variant 2: remove vowels (a, e, i, o, u, y) in any case.
void removeVowels(std::vector<std::string>& vec) {
  auto isVowel = [](char c) {
    char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' ||
           lower == 'u' || lower == 'y';
  };
  std::for_each(vec.begin(), vec.end(), [&isVowel](std::string& s) {
    s.erase(std::remove_if(s.begin(), s.end(), isVowel), s.end());
  });
}

// Lambda with capture by REFERENCE: word is referenced, not copied.
void writeSearchResult(std::ofstream& out, const std::vector<std::string>& vec,
                       const std::string& word) {
  auto containsWord = [&word](const std::string& s) {
    return s.find(word) != std::string::npos;
  };
  auto it = std::find_if(vec.begin(), vec.end(), containsWord);
  out << "4) Searching for word \"" << word << "\":\n";
  if (it != vec.end()) {
    out << "  Found in: " << *it << "\n\n";
  } else {
    out << "  Not found\n\n";
  }
}

int countCharsExcludingUnderscore(const std::vector<std::string>& vec) {
  return std::accumulate(
      vec.begin(), vec.end(), 0, [](int sum, const std::string& s) {
        return sum + static_cast<int>(std::count_if(
                         s.begin(), s.end(), [](char c) { return c != '_'; }));
      });
}

std::vector<int> getLengths(const std::vector<std::string>& vec) {
  std::vector<int> lengths;
  lengths.reserve(vec.size());
  std::transform(
      vec.begin(), vec.end(), std::back_inserter(lengths),
      [](const std::string& s) { return static_cast<int>(s.length()); });
  return lengths;
}

void processAndWrite(const std::vector<std::string>& lines, int threshold,
                     const std::string& search_word, std::ofstream& out) {
  writeStringVector(out, lines, "1) Original strings");
  auto filtered = filterShort(lines, threshold);
  writeStringVector(
      out, filtered,
      "2) After removing strings shorter than " + std::to_string(threshold));
  removeVowels(filtered);
  writeStringVector(out, filtered, "3) After removing vowels");
  writeSearchResult(out, filtered, search_word);
  out << "5) Total character count (excluding '_'): "
      << countCharsExcludingUnderscore(filtered) << "\n\n";
  writeIntVector(out, getLengths(filtered), "6) String lengths");
}

}  // namespace

int main() {
  auto lines = readLines("input.txt");
  int threshold = 0;
  std::string search_word;
  std::cout << "Enter minimum string length threshold: ";
  std::cin >> threshold;
  std::cout << "Enter search word: ";
  std::cin >> search_word;
  std::ofstream output("output.txt");
  processAndWrite(lines, threshold, search_word, output);
  return 0;
}
