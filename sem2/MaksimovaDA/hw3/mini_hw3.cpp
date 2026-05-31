#include <Windows.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  std::ifstream input_file("input.txt");
  if (!input_file.is_open()) {
    std::cout << "no input.txt" << std::endl;
    return 1;
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(input_file, line)) {
    lines.push_back(line);
  }

  input_file.close();

  int threshold;
  std::cout << "enter threshold: ";
  std::cin >> threshold;

  std::vector<std::string> original_lines = lines;

  auto isShorterThanThreshold = [threshold](const std::string& str) {
    return str.length() < threshold;
  };

  auto new_end =
      std::remove_if(lines.begin(), lines.end(), isShorterThanThreshold);
  lines.erase(new_end, lines.end());

  std::vector<std::string> after_remove_lines = lines;

  auto replaceSpaces = [](std::string& str) {
    for (char& c : str) {
      if (c == ' ') {
        c = '_';
      }
    }
  };

  std::vector<std::string> after_replace_lines = after_remove_lines;
  for (std::string& str : after_replace_lines) {
    replaceSpaces(str);
  }

  std::string search_word;
  std::cout << "enter search word: ";
  std::cin >> search_word;

  auto containsWord = [&](const std::string& str) {
    return str.find(search_word) != std::string::npos;
  };

  auto it = std::find_if(after_replace_lines.begin(), after_replace_lines.end(),
                         containsWord);

  std::string search_result;
  if (it != after_replace_lines.end()) {
    search_result = *it;
  } else {
    search_result = "no line";
  }

  int total_chars = 0;

  for (const std::string& str : after_replace_lines) {
    for (char c : str) {
      if (c != '_') {
        total_chars++;
      }
    }
  }

  std::vector<int> line_lengths;

  for (const std::string& str : after_replace_lines) {
    line_lengths.push_back(str.length());
  }

  std::ofstream output_file("output.txt");
  if (!output_file.is_open()) {
    std::cout << "no output.txt" << std::endl;
    return 1;
  }

  auto printLines = [&output_file](const std::vector<std::string>& vec,
                                  const std::string& title) {
    output_file << title << std::endl;
    for (const std::string& str : vec) {
      output_file << str << std::endl;
    }
    output_file << std::endl;
  };

  printLines(original_lines, "original vector:");
  printLines(after_remove_lines, "vector after delete short words:");
  printLines(after_replace_lines, "vector after replacing spaces with '_':");

  output_file << "search result " << search_word
             << ":" << std::endl;
  output_file << search_result << std::endl << std::endl;

  output_file << "simbols count without '_': " << total_chars
             << std::endl;

  output_file << "lengths:" << std::endl;
  for (int len : line_lengths) {
    output_file << len << std::endl;
  }

  output_file.close();

  return 0;
}