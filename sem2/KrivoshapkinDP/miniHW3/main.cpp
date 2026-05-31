#include <iostream>

#include "stringProcessor.h"

int main() {
  StringProcessor processor;
  processor.readInput("input.txt");
  int threshold;
  std::cin >> threshold;
  std::string searchWord;
  std::cin >> searchWord;
  processor.removeShortStrings(threshold);
  processor.removeVowels();
  std::string found = processor.searchWord(searchWord);
  int totalChars = processor.countCharsWithoutUnderscores();
  std::vector<int> lengths = processor.getLengths();
  processor.outputResults("output.txt", found, totalChars, lengths);
  return 0;
}
