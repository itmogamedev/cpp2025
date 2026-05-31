#pragma once

#include <string>
#include <vector>

class StringProcessor {
 public:
  void readFromFile(const std::string& filename);
  void writeToFile(const std::string& filename);
  void appendResults(const std::string& filename, const std::string& word,
                     bool found, int totalChars,
                     const std::vector<int>& lengths);
  void removeShortStrings(int threshold);
  void replaceSpacesWithUnderscores();
  bool searchWord(const std::string& word);
  int countCharactersWithoutUnderscores();
  std::vector<int> getStringLengths();

  const std::vector<std::string>& getOriginalStrings() const;
  const std::vector<std::string>& getFilteredStrings() const;
  const std::vector<std::string>& getReplacedStrings() const;

  void processStrings(const std::string& inputFile, const std::string& outputFile);

 private:
  std::vector<std::string> originalStrings;
  std::vector<std::string> filteredStrings;
  std::vector<std::string> replacedStrings;
};
