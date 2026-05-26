#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void print_lines(std::vector<std::string> lines, std::ofstream& output) {
  std::for_each(lines.begin(), lines.end(),
                [&](const std::string& str) { output << str << '\n'; });
}

void task3(std::ifstream& input, std::ofstream& output) {
  std::vector<std::string> lines;

  // Input

  std::string line;
  while (std::getline(input, line)) {
    lines.push_back(line);
  }
  input.close();

  output << "Input file:\n";
  print_lines(lines, output);

  // Remove short lines

  int length;
  std::cout << "Enter minimal desired length: ";
  std::cin >> length;

  std::erase_if(lines, [=](const std::string& str) {
    bool result = str.length() < length;
    return result;
  });

  output << "\nAfter short lines were removed:\n";
  print_lines(lines, output);

  // Replace all space characters with underscores

  std::for_each(lines.begin(), lines.end(), [](std::string& str) {
    std::for_each(str.begin(), str.end(), [](char& c) {
      if (std::isspace(c)) c = '_';
    });
  });

  output << "\nSpaces replaced with underscores:\n";
  print_lines(lines, output);

  // Find user-specified word

  std::string word;
  std::cout << "Enter a word to search for: ";
  std::cin >> word;

  output << "\nSearch for word \"" << word << "\":\n";
  std::for_each(lines.begin(), lines.end(), [&](const std::string& str) {
    if (str.find(word) != std::string::npos) output << str << '\n';
  });

  // Count characters

  std::vector<int> lengths;
  std::for_each(lines.begin(), lines.end(), [&](const std::string& str) {
    int n = 0;
    std::for_each(str.begin(), str.end(), [&](const char& c) {
      if (c != '_') n++;
    });
    lengths.push_back(n);
  });

  output << "\nNumber of non-space characters on each line:\n";
  std::for_each(lengths.begin(), lengths.end(),
                [&](const int& n) { output << n << '\n'; });

  output << "\nTOTAL:\n";
  output << std::accumulate(lengths.begin(), lengths.end(), 0);
}

int main() {
  std::ifstream input("input.txt");
  std::ofstream output("output.txt");

  task3(input, output);

  input.close();
  output.close();

  return 0;
}