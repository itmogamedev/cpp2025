#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <string>
#include <vector>

class FileProcessor {
 public:
  void run();

 private:
  void process(int threshold, const std::string& search_word);

  void readInputFile(const std::string& filename);

  void writeResults(const std::string& filename) const;

  static const std::string kInputFile;
  static const std::string kOutputFile;
  static const char kUnderscore;

  std::vector<std::string> original_lines;
  std::vector<std::string> after_remove;
  std::vector<std::string> after_replace;
  bool word_found = false;
  int total_chars_no_underscore = 0;
  std::vector<int> line_lengths;
};

#endif
