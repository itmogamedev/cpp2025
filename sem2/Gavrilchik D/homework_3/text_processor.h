#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#include <string>
#include <vector>

class TextProcessor {
 public:
  TextProcessor(const std::string& input_file_name,
                const std::string& output_file_name);

  void run();

 private:
  std::string input_file_name;
  std::string output_file_name;

  std::vector<std::string> readLines() const;
  std::vector<std::string> removeShortLines(
      const std::vector<std::string>& lines, int min_length) const;
  std::vector<std::string> removeVowels(
      const std::vector<std::string>& lines) const;
  std::string findLineWithWord(const std::vector<std::string>& lines,
                               const std::string& search_word) const;
  int countSymbolsWithoutUnderscores(
      const std::vector<std::string>& lines) const;
  std::vector<int> getLineLengths(const std::vector<std::string>& lines) const;

  bool isVowel(char symbol) const;
  void writeResult(const std::vector<std::string>& original_lines,
                   const std::vector<std::string>& filtered_lines,
                   const std::vector<std::string>& changed_lines,
                   const std::string& found_line,
                   int total_symbols,
                   const std::vector<int>& lengths) const;
};

#endif