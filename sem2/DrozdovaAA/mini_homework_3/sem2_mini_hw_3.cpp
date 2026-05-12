#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void printStringVector(const std::vector<std::string>& vec,
                       std::ofstream& out) {
  for (const auto& str : vec) {
    out << str << "\n";
  }
}

void runProgram() {
  std::ifstream file_contents("input.txt");
  std::vector<std::string> original_lines;
  std::string current_line;

  while (std::getline(file_contents,
                      current_line)) {  // считываем в вектор с текущей строкой
    original_lines.push_back(current_line);
  }
  file_contents.close();

  // получаем данные от пользователя
  int length_threshold = 0;
  std::cout << "length threshold: ";
  std::cin >> length_threshold;

  std::string search_word;
  std::cout << "search word: ";
  std::cin >> search_word;

  std::ofstream out_file("output.txt");
  if (!out_file.is_open()) {
    std::cerr << "recording error\n";
    return;
  }

  out_file << "original vector:\n";
  printStringVector(original_lines, out_file);

  // 1 - удаление всех строк меньше заданного значения
  std::vector<std::string> filtered_lines = original_lines;  // копия строк
  filtered_lines.erase(
      std::remove_if(filtered_lines.begin(), filtered_lines.end(),
                     [length_threshold](const std::string& str) {
                       return str.length() <
                              static_cast<size_t>(length_threshold);
                     }),
      filtered_lines.end());

  out_file << "\n vector after removing short lines:\n";
  printStringVector(filtered_lines, out_file);

  // 2 - замена пробелов на _
  std::vector<std::string> underscored_lines =
      filtered_lines;  // копия отфитрованного
  std::for_each(
      underscored_lines.begin(), underscored_lines.end(),
      [](std::string& str) { std::replace(str.begin(), str.end(), ' ', '_'); });

  out_file << "\n vector after replacing spaces with '_': \n";
  printStringVector(underscored_lines, out_file);

  // 3 - поиск строки, содержащей слово пользователя
  auto find_it =
      std::find_if(filtered_lines.begin(), filtered_lines.end(),
                   [&search_word](const std::string& str) {
                     return str.find(search_word) != std::string::npos;
                   });

  out_file << "\n search result for word '" << search_word << "' \n";
  if (find_it != filtered_lines.end()) {
    // индекс найденной строки
    auto index = std::distance(filtered_lines.begin(), find_it);
    out_file << underscored_lines[index] << "\n";
  } else {
    out_file << "word not found\n";
  }

  // 4 - общее кол-во символов без учёта _
  size_t total_chars = 0;
  std::for_each(underscored_lines.begin(), underscored_lines.end(),
                [&total_chars](const std::string& str) {
                  total_chars += std::count_if(str.begin(), str.end(),
                                               [](char c) { return c != '_'; });
                });

  out_file << "\n total characters without '_': \n";
  out_file << total_chars << "\n";

  // 5 - вектор чисел с длинами строк
  std::vector<int> string_lengths;
  string_lengths.reserve(underscored_lines.size());
  std::transform(
      underscored_lines.begin(), underscored_lines.end(),
      std::back_inserter(string_lengths),
      [](const std::string& str) { return static_cast<int>(str.length()); });

  out_file << "\n vector of string lengths: \n";
  for (int len : string_lengths) {
    out_file << len << " ";
  }
  out_file << "\n";

  out_file.close();
  std::cout << "program completed" << std::endl;
}

int main() {
  runProgram();
  return 0;
}
