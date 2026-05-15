#ifndef STRINGPROCESSOR_H
#define STRINGPROCESSOR_H

#include <string>
#include <vector>

class StringProcessor {
 public:
  void readInput(const std::string& filename);
  void removeShortStrings(int threshold);
  void removeVowels();
  std::string searchWord(const std::string& word) const;
  int countCharsWithoutUnderscores() const;
  std::vector<int> getLengths() const;
  void outputResults(const std::string& filename, const std::string& foundLine,
                     int totalChars, const std::vector<int>& lengths) const;

 private:
  std::vector<std::string> original_lines;
  std::vector<std::string> lines_after_short;
  std::vector<std::string> lines_after_vowels;
};

#endif
