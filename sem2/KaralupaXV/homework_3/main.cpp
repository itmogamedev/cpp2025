#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ifstream input_file("input.txt");

  std::vector<std::string> lines;
  std::string line;

  while (std::getline(input_file, line)) {
    lines.push_back(line);
  }
  input_file.close();

  std::vector<std::string> initial = lines;

  int min_length;
  std::cout << "Input min length: ";
  std::cin >> min_length;

  lines.erase(std::remove_if(lines.begin(), lines.end(),
                             [min_length](std::string &s) {
                               return s.length() < min_length;
                             }),
              lines.end());

  std::vector<std::string> filtered = lines;

  std::string removed_letters = "aeiouy";

  std::for_each(
      lines.begin(), lines.end(), [&removed_letters](std::string &str) {
        str.erase(std::remove_if(str.begin(), str.end(),
                                 [&removed_letters](char c) {
                                   return removed_letters.find(std::tolower(
                                              c)) != std::string::npos;
                                 }),
                  str.end());
      });

  std::vector<std::string> removed = lines;

  std::string find_word;
  std::cout << "Input word to find: ";
  std::cin >> find_word;

  auto found_string = std::find_if(
      initial.begin(), initial.end(), [&find_word](std::string &str) {
        return str.find(find_word) != std::string::npos;
      });

  int total_length = 0;
  std::vector<int> lines_length;

  std::for_each(lines.begin(), lines.end(),
                [&lines_length, &total_length](std::string &str) {
                  lines_length.push_back(str.length());
                  total_length += str.length();
                });

  std::ofstream output_file("output.txt");

  output_file << "Initial file: \n";
  std::for_each(
      initial.begin(), initial.end(),
      [&output_file](std::string &str) { output_file << str << "\n"; });
  output_file << "\n";

  output_file << "Lines after filtering: \n";
  std::for_each(
      filtered.begin(), filtered.end(),
      [&output_file](std::string &str) { output_file << str << "\n"; });
  output_file << "\n";

  output_file << "Lines after removing vowels: \n";
  std::for_each(
      removed.begin(), removed.end(),
      [&output_file](std::string &str) { output_file << str << "\n"; });
  output_file << "\n";

  output_file << "Word " << find_word << " ";
  if (found_string == initial.end()) {
    output_file << "not found\n";
  } else {
    output_file << "found in string: ";
    output_file << *found_string << "\n";
  }

  output_file << "Total length: " << total_length << "\n";

  output_file << "Array of new lengths: ";
  std::for_each(lines_length.begin(), lines_length.end(),
                [&output_file](int length) { output_file << length << " "; });

  output_file << std::endl;
  output_file.close();

  return 0;
}