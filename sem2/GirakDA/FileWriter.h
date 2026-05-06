#pragma once
#include <string>
#include <vector>

class FileWriter {
 private:
  std::string filename;

 public:
  explicit FileWriter(const std::string& file);
  void process(const std::vector<int>& vec);
};
