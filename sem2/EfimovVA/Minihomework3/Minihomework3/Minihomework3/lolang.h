#ifndef LOLANG_H
#define LOLANG_H

#include <fstream>
#include <string>
#include <vector>

class TextProcessor {
 private:
  std::vector<std::string> original_lines;
  std::vector<std::string> modified_lines;
  std::string input_filename;
  std::string output_filename;

  void writeVectorToFile(std::ofstream& out_file, const std::string& title,
                         const std::vector<std::string>& vec);

 public:
  TextProcessor(const std::string& in_file, const std::string& out_file);

  void processText(int min_length, const std::string& search_word);
};

#endif