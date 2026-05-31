#ifndef STRING_ANALIZE_H
#define STRING_ANALIZE_H

#include <string>
#include <vector>

class StringAnalize {
 public:
  void processFiles(const std::string& input_filename,
                    const std::string& output_filename, int threshold,
                    const std::string& search_word);

 private:
  std::vector<std::string> string_data;
};

#endif  //  STRING_ANALIZE_H
