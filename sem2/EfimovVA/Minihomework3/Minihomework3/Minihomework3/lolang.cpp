#include "lolang.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>

TextProcessor::TextProcessor(const std::string& in_file,
                             const std::string& out_file) {
  input_filename = in_file;
  output_filename = out_file;
}

// Реализуем запись
void TextProcessor::writeVectorToFile(std::ofstream& out_file,
                                      const std::string& title,
                                      const std::vector<std::string>& vec) {
  out_file << "=== " << title << " ===\n";
  for (size_t i = 0; i < vec.size(); ++i) {
    out_file << vec[i] << '\n';
  }
  out_file << '\n';
}

void TextProcessor::processText(int min_length,
                                const std::string& search_word) {
  std::ifstream in_file(input_filename);
  if (!in_file.is_open()) {
    std::cout << "Che za xuinyu ti visral?????? " << input_filename << '\n';
    return;
  }

  // Читаем строчки
  std::string line;
  while (std::getline(in_file, line)) {
    original_lines.push_back(line);
  }
  in_file.close();

  modified_lines = original_lines;

  // Удаляем строку меньше заданного порога
  modified_lines.erase(
      std::remove_if(modified_lines.begin(), modified_lines.end(),
                     [min_length](const std::string& s) {
                       return s.length() < static_cast<size_t>(min_length);
                     }),
      modified_lines.end());

  // Сохраняем результат
  std::vector<std::string> lines_after_filter = modified_lines;

  // Удаление гласных букв
  for (size_t i = 0; i < modified_lines.size(); ++i) {
    modified_lines[i].erase(
        std::remove_if(modified_lines[i].begin(), modified_lines[i].end(),
                       [](char c) {
                         char lower_c = std::tolower(c);
                         return lower_c == 'a' || lower_c == 'e' ||
                                lower_c == 'i' || lower_c == 'o' ||
                                lower_c == 'u' || lower_c == 'y';
                       }),
        modified_lines[i].end());
  }

  // Поиск строки с заданным словом
  std::string search_result = "Word not found.";
  auto find_it = std::find_if(modified_lines.begin(), modified_lines.end(),
                              [&search_word](const std::string& s) {
                                return s.find(search_word) != std::string::npos;
                              });

  if (find_it != modified_lines.end()) {
    search_result = *find_it;
  }

  // Подсчитываем символы без учета '_'
  int total_chars_count = 0;
  std::for_each(modified_lines.begin(), modified_lines.end(),
                [&total_chars_count](const std::string& s) {
                  for (size_t i = 0; i < s.length(); ++i) {
                    if (s[i] != '_') {
                      total_chars_count++;
                    }
                  }
                });

  std::vector<int> string_lengths;
  for (size_t i = 0; i < modified_lines.size(); ++i) {
    string_lengths.push_back(static_cast<int>(modified_lines[i].length()));
  }

  std::ofstream out_file(output_filename);
  if (!out_file.is_open()) {
    std::cout << "Cheza xuynu ti visral???? " << output_filename << '\n';
    return;
  }

  writeVectorToFile(out_file, "Original strings", original_lines);
  writeVectorToFile(out_file, "Strings after removing short ones",
                    lines_after_filter);
  writeVectorToFile(out_file, "Strings after removing vowels", modified_lines);

  out_file << "Search result\n";
  out_file << search_result << "\n\n";

  out_file << "Total characters without '_'\n";
  out_file << total_chars_count << "\n\n";

  out_file << "Vector of string lengths\n";
  for (size_t i = 0; i < string_lengths.size(); ++i) {
    out_file << string_lengths[i] << ' ';
  }
  out_file << '\n';

  out_file.close();
  std::cout << "Yayyayyay " << output_filename
            << " GO CHECK THE EINSTEIN FILES0))).\n";
}

int main() {
  std::cout << "Enter minimum string length threshold: ";
  int min_length = 0;
  std::cin >> min_length;

  std::cout << "Enter a word to search: ";
  std::string search_word;
  std::cin >> search_word;

  TextProcessor processor("input.txt", "output.txt");
  processor.processText(min_length, search_word);

  return 0;
}