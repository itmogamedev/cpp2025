#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> readLines(const std::string& filename) {
  std::vector<std::string> lines;
  std::ifstream file(filename);
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  return lines;
}

void writeLines(std::ostream& out, const std::vector<std::string>& lines) {
  for (const auto& line : lines) {
    out << line << "\n";
  }
}

void writeInts(std::ostream& out, const std::vector<int>& nums) {
  for (size_t i = 0; i < nums.size(); ++i) {
    if (i > 0) out << " ";
    out << nums[i];
  }
  out << "\n";
}

int main() {
  std::vector<std::string> lines = readLines("input.txt");

  int threshold;
  std::cout << "Enter minimum string length: ";
  std::cin >> threshold;

  std::string search_word;
  std::cout << "Enter word to search: ";
  std::cin >> search_word;

  std::ofstream out("output.txt");

  out << "=== Original strings ===\n";
  writeLines(out, lines);

  // Удаление строк короче порога (лямбда, захват по значению)
  std::vector<std::string> filtered = lines;
  filtered.erase(std::remove_if(filtered.begin(), filtered.end(),
                                [threshold](const std::string& s) {
                                  return static_cast<int>(s.size()) < threshold;
                                }),
                 filtered.end());

  out << "\n=== After removing strings shorter than " << threshold << " ===\n";
  writeLines(out, filtered);

  // Вариант 1: замена пробелов на подчёркивания
  std::vector<std::string> replaced = filtered;
  std::for_each(replaced.begin(), replaced.end(), [](std::string& s) {
    std::replace(s.begin(), s.end(), ' ', '_');
  });

  out << "\n=== After replacing spaces with '_' ===\n";
  writeLines(out, replaced);

  // Поиск строки, содержащей слово (лямбда, захват по ссылке)
  auto it = std::find_if(replaced.begin(), replaced.end(),
                         [&search_word](const std::string& s) {
                           return s.find(search_word) != std::string::npos;
                         });

  out << "\n=== Search result for '" << search_word << "' ===\n";
  if (it != replaced.end()) {
    out << "Found: " << *it << "\n";
  } else {
    out << "Not found\n";
  }

  // Подсчёт символов без учёта подчёркиваний
  int total_chars = 0;
  std::for_each(
      replaced.begin(), replaced.end(), [&total_chars](const std::string& s) {
        total_chars += static_cast<int>(
            std::count_if(s.begin(), s.end(), [](char c) { return c != '_'; }));
      });

  out << "\n=== Total characters (excluding '_') ===\n";
  out << total_chars << "\n";

  // Вектор длин строк
  std::vector<int> lengths;
  std::transform(
      replaced.begin(), replaced.end(), std::back_inserter(lengths),
      [](const std::string& s) { return static_cast<int>(s.size()); });

  out << "\n=== String lengths ===\n";
  writeInts(out, lengths);

  std::cout << "Results written to output.txt\n";
  return 0;
}
