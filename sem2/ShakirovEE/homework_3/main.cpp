#include <windows.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static std::vector<std::string> readLines(const std::string& filename) {
  std::vector<std::string> lines;
  std::ifstream in(filename);
  std::string line;
  while (std::getline(in, line)) lines.push_back(line);
  return lines;
}

static void writeLines(std::ofstream& out, const std::string& title,
                       const std::vector<std::string>& lines) {
  out << title << ":\n";
  for (const auto& l : lines) out << l << '\n';
  out << '\n';
}

static void writeInts(std::ofstream& out, const std::string& title,
                      const std::vector<int>& vec) {
  out << title << ":\n";
  for (size_t i = 0; i < vec.size(); ++i)
    out << vec[i] << (i + 1 < vec.size() ? " " : "");
  out << "\n\n";
}

static void runProcessing(int threshold, const std::string& search_word) {
  std::vector<std::string> original = readLines("input.txt");

  // лямбда с захватом по значению
  std::vector<std::string> after_remove = original;
  auto it = std::remove_if(after_remove.begin(), after_remove.end(),
                           [threshold](const std::string& s) {
                             return s.length() < (size_t)threshold;
                           });
  after_remove.erase(it, after_remove.end());

  // Замена пробелов на '_' (вариант 1)
  std::vector<std::string> after_replace = after_remove;
  for (auto& line : after_replace)
    std::replace(line.begin(), line.end(), ' ', '_');

  // лямбда с захватом по ссылке
  auto found_it =
      std::find_if(after_replace.begin(), after_replace.end(),
                   [&search_word](const std::string& s) {
                     return s.find(search_word) != std::string::npos;
                   });
  std::string found_line = (found_it != after_replace.end()) ? *found_it : "";

  int total_chars = 0;
  for (const auto& line : after_replace)
    for (char ch : line)
      if (ch != '_') ++total_chars;

  std::vector<int> lengths;
  for (const auto& line : after_replace) lengths.push_back((int)line.length());

  std::ofstream out("output.txt");
  writeLines(out, "Исходный вектор строк", original);
  writeLines(out, "После удаления коротких строк", after_remove);
  writeLines(out, "После замены пробелов на '_'", after_replace);
  out << "Результат поиска слова \"" << search_word << "\":\n";
  out << (found_line.empty() ? "не найдено" : found_line) << "\n\n";
  out << "Общее количество символов без '_': " << total_chars << "\n\n";
  writeInts(out, "Вектор длин строк", lengths);
}

int main() {
  std::setlocale(LC_ALL, "Russian");
  int threshold;
  std::string search_word;
  std::cout << "Порог длины: ";
  std::cin >> threshold;
  std::cout << "Слово для поиска: ";
  std::cin >> search_word;
  runProcessing(threshold, search_word);
  std::cout << "Готово. Результат в output.txt\n";
  return 0;
}
