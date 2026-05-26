#include "../Header Files/text_processor.h"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <numeric>

namespace homework {

std::vector<std::string> readLinesFromFile(const std::string& filename) {
  std::vector<std::string> lines;
  std::ifstream input_file(filename);
  std::string line;
  while (std::getline(input_file, line)) {
    lines.push_back(line);
  }
  return lines;
}

std::vector<std::string> filterShortLines(const std::vector<std::string>& lines,
                                          std::size_t threshold) {
  std::vector<std::string> result;

  auto isLongEnough = [threshold](const std::string& s) {
    return s.length() >= threshold;
  };
  std::copy_if(lines.begin(), lines.end(), std::back_inserter(result),
               isLongEnough);
  return result;
}

std::vector<std::string> replaceSpacesWithUnderscore(
    const std::vector<std::string>& lines) {
  std::vector<std::string> result;
  result.reserve(lines.size());

  auto replaceSpaces = [](std::string s) {
    std::replace(s.begin(), s.end(), ' ', '_');
    return s;
  };
  std::transform(lines.begin(), lines.end(), std::back_inserter(result),
                 replaceSpaces);
  return result;
}

std::string findFirstLineWithWord(const std::vector<std::string>& lines,
                                  const std::string& word) {
  auto containsWord = [&word](const std::string& s) {
    return s.find(word) != std::string::npos;
  };
  auto it = std::find_if(lines.begin(), lines.end(), containsWord);
  if (it != lines.end()) {
    return *it;
  }
  return std::string();
}

std::size_t countCharactersWithoutUnderscore(
    const std::vector<std::string>& lines) {
  return std::accumulate(
      lines.begin(), lines.end(), static_cast<std::size_t>(0),
      [](std::size_t sum, const std::string& s) {
        return sum + static_cast<std::size_t>(std::count_if(
                         s.begin(), s.end(), [](char c) { return c != '_'; }));
      });
}

std::vector<int> computeLineLengths(const std::vector<std::string>& lines) {
  std::vector<int> lengths;
  lengths.reserve(lines.size());
  std::transform(
      lines.begin(), lines.end(), std::back_inserter(lengths),
      [](const std::string& s) { return static_cast<int>(s.length()); });
  return lengths;
}

namespace {

void writeStringVector(std::ofstream& out, const std::string& title,
                       const std::vector<std::string>& vec) {
  out << title << " (" << vec.size() << " lines):\n";
  if (vec.empty()) {
    out << "  [empty]\n";
  } else {
    for (std::size_t i = 0; i < vec.size(); ++i) {
      out << "  [" << i << "] " << vec[i] << "\n";
    }
  }
  out << "\n";
}

void writeIntVector(std::ofstream& out, const std::string& title,
                    const std::vector<int>& vec) {
  out << title << " (" << vec.size() << " values):\n  [";
  for (std::size_t i = 0; i < vec.size(); ++i) {
    out << vec[i];
    if (i + 1 < vec.size()) {
      out << ", ";
    }
  }
  out << "]\n\n";
}

}  // namespace

void writeResultsToFile(const std::string& filename,
                        const std::vector<std::string>& original,
                        const std::vector<std::string>& filtered,
                        const std::vector<std::string>& replaced,
                        std::size_t threshold, const std::string& search_word,
                        const std::string& search_result,
                        std::size_t character_count,
                        const std::vector<int>& lengths) {
  std::ofstream out(filename);
  out << "===== SUMO TATAMI <3 <3 <3 =====\n\n";
  out << "===== Mini-homework 3 (Variant 1) =====\n\n";
  writeStringVector(out, "1. Original lines from input.txt", original);
  out << "Threshold for short lines: " << threshold << "\n\n";
  writeStringVector(out, "2. After removing short lines", filtered);
  writeStringVector(out, "3. After replacing spaces with '_'", replaced);
  out << "4. Search for word \"" << search_word << "\":\n";
  if (search_result.empty()) {
    out << "  [no line containing this word]\n\n";
  } else {
    out << "  found in: " << search_result << "\n\n";
  }
  out << "5. Total characters (excluding '_'): " << character_count << "\n\n";
  writeIntVector(out, "6. Line lengths", lengths);
}

void runHomework(const std::string& input_filename,
                 const std::string& output_filename, std::size_t threshold,
                 const std::string& search_word) {
  auto original = readLinesFromFile(input_filename);
  auto filtered = filterShortLines(original, threshold);
  auto replaced = replaceSpacesWithUnderscore(filtered);
  auto found = findFirstLineWithWord(replaced, search_word);
  auto count = countCharactersWithoutUnderscore(replaced);
  auto lengths = computeLineLengths(replaced);
  writeResultsToFile(output_filename, original, filtered, replaced, threshold,
                     search_word, found, count, lengths);
}

}  // namespace homework
