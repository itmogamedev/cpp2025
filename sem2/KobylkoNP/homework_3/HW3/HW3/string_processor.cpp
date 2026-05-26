#include "string_processor.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>

void StringProcessor::readFromFile(const std::string& filename) {
  std::ifstream file(filename);
  std::string line;
  while (std::getline(file, line)) {
    originalStrings.push_back(line);
  }
  file.close();
}

void StringProcessor::writeToFile(const std::string& filename) {
  std::ofstream file(filename);

  file << "Original vector of strings:\n";
  for (const auto& str : originalStrings) {
    file << str << '\n';
  }

  file << "\nVector of strings after removing short strings:\n";
  for (const auto& str : filteredStrings) {
    file << str << '\n';
  }

  file << "\nVector of strings after replacing spaces with \"_\":\n";
  for (const auto& str : replacedStrings) {
    file << str << '\n';
  }

  file.close();
}

void StringProcessor::appendResults(const std::string& filename,
                                    const std::string& word, bool found,
                                    int totalChars,
                                    const std::vector<int>& lengths) {
  std::ofstream file(filename, std::ios::app);

  file << "\nSearch result for word \"" << word
       << "\": " << (found ? "found" : "not found") << '\n';
  file << "Total number of characters without \"_\": " << totalChars << '\n';
  file << "Vector of string lengths: ";
  for (int len : lengths) {
    file << len << ' ';
  }
  file << '\n';
  file.close();
}

void StringProcessor::removeShortStrings(int threshold) {
  filteredStrings.clear();
  auto filterLambda = [threshold](const std::string& str) {
    return str.length() >= static_cast<size_t>(threshold);
  };

  std::copy_if(originalStrings.begin(), originalStrings.end(),
               std::back_inserter(filteredStrings), filterLambda);
}

void StringProcessor::replaceSpacesWithUnderscores() {
  replacedStrings = filteredStrings;
  auto replaceLambda = [](std::string& str) {
    std::replace(str.begin(), str.end(), ' ', '_');
  };

  std::for_each(replacedStrings.begin(), replacedStrings.end(), replaceLambda);
}

bool StringProcessor::searchWord(const std::string& word) {
  auto searchLambda = [&word](const std::string& str) {
    return str.find(word) != std::string::npos;
  };

  return std::any_of(replacedStrings.begin(), replacedStrings.end(),
                     searchLambda);
}

int StringProcessor::countCharactersWithoutUnderscores() {
  return std::accumulate(replacedStrings.begin(), replacedStrings.end(), 0,
                         [](int acc, const std::string& str) {
                           return acc + static_cast<int>(std::count_if(
                                            str.begin(), str.end(),
                                            [](char c) { return c != '_'; }));
                         });
}

std::vector<int> StringProcessor::getStringLengths() {
  std::vector<int> lengths;
  auto lengthLambda = [](const std::string& str) {
    return static_cast<int>(str.length());
  };

  std::transform(replacedStrings.begin(), replacedStrings.end(),
                 std::back_inserter(lengths), lengthLambda);

  return lengths;
}

const std::vector<std::string>& StringProcessor::getOriginalStrings() const {
  return originalStrings;
}

const std::vector<std::string>& StringProcessor::getFilteredStrings() const {
  return filteredStrings;
}

const std::vector<std::string>& StringProcessor::getReplacedStrings() const {
  return replacedStrings;
}

void StringProcessor::processStrings(const std::string& inputFile,
                                     const std::string& outputFile) {
  readFromFile(inputFile);

  int threshold;
  std::cout << "Enter string length threshold: ";
  std::cin >> threshold;
  removeShortStrings(threshold);

  replaceSpacesWithUnderscores();

  std::string wordToSearch;
  std::cout << "Enter word to search: ";
  std::cin >> wordToSearch;

  bool found = searchWord(wordToSearch);
  int totalChars = countCharactersWithoutUnderscores();
  std::vector<int> lengths = getStringLengths();

  writeToFile(outputFile);
  appendResults(outputFile, wordToSearch, found, totalChars, lengths);
}
