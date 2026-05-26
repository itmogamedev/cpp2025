#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> readLines(const std::string& filename) {
  std::vector<std::string> lines;
  std::ifstream infile(filename);
  std::string temp;
  while (std::getline(infile, temp)) {
    lines.push_back(temp);
  }
  return lines;
}

void removeShortLines(std::vector<std::string>& lines, int threshold) {
  auto it = std::remove_if(lines.begin(), lines.end(),
                           [threshold](const std::string& s) {
                             return (int)s.length() < threshold;
                           });
  lines.erase(it, lines.end());
}

void processVowels(std::vector<std::string>& lines) {
  const std::string vowels = "aeiouyAEIOUY";
  for (auto& line : lines) {
    auto v_it = std::remove_if(line.begin(), line.end(), [&vowels](char c) {
      return vowels.find(c) != std::string::npos;
    });
    line.erase(v_it, line.end());
  }
}

std::string findTargetWord(const std::vector<std::string>& lines,
                           const std::string& target) {
  bool found = false;
  std::string result = "Not found";
  std::for_each(lines.begin(), lines.end(),
                [&target, &found, &result](const std::string& s) {
                  if (!found && s.find(target) != std::string::npos) {
                    found = true;
                    result = s;
                  }
                });
  return result;
}

int calculateTotalChars(const std::vector<std::string>& lines) {
  int total = 0;
  for (const auto& s : lines) total += (int)s.length();
  return total;
}

std::vector<int> mapLengths(const std::vector<std::string>& lines) {
  std::vector<int> lengths;
  for (const auto& s : lines) lengths.push_back((int)s.length());
  return lengths;
}

int main() {
  int threshold;
  std::string query;

  std::cout << "Enter min length: ";
  std::cin >> threshold;
  std::cout << "Enter search word: ";
  std::cin >> query;

  auto original = readLines("input.txt");
  auto lines = original;

  removeShortLines(lines, threshold);
  auto after_filter = lines;

  processVowels(lines);
  auto after_processing = lines;

  std::string search_res = findTargetWord(lines, query);
  int char_count = calculateTotalChars(lines);
  auto lengths_vec = mapLengths(lines);

  std::ofstream outfile("output.txt");

  outfile << "Original:\n";
  for (const auto& s : original) outfile << s << "\n";

  outfile << "\nFiltered:\n";
  for (const auto& s : after_filter) outfile << s << "\n";

  outfile << "\nProcessed (No Vowels):\n";
  for (const auto& s : after_processing) outfile << s << "\n";

  outfile << "\nSearch Result: " << search_res << "\n";
  outfile << "Total Characters: " << char_count << "\n";
  outfile << "Lengths Vector: ";
  for (int l : lengths_vec) outfile << l << " ";

  return 0;
}