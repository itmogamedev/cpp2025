#include "text_processor.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace {

// Вспомогательная функция для проверки, является ли символ гласной буквой
bool isVowel(char ch) {
  char lower_ch = std::tolower(static_cast<unsigned char>(ch));
  return lower_ch == 'a' || lower_ch == 'e' || lower_ch == 'i' ||
         lower_ch == 'o' || lower_ch == 'u' || lower_ch == 'y';
}

}  // namespace

void processTextFiles(const std::string& input_path,
                      const std::string& output_path) {
  std::ifstream input_file(input_path);
  std::ofstream output_file(output_path);

  if (!input_file.is_open() || !output_file.is_open()) {
    std::cerr << "Error opening files!" << std::endl;
    return;
  }

  // 1. Считывание всех строк из файла
  std::vector<std::string> original_lines;
  std::string current_line;
  while (std::getline(input_file, current_line)) {
    original_lines.push_back(current_line);
  }

  size_t length_threshold = 0;
  std::cout << "Enter line length threshold: ";
  std::cin >> length_threshold;

  std::string search_word;
  std::cout << "Enter word to search for: ";
  std::cin >> search_word;

  // 2. Удаление коротких строк
  std::vector<std::string> filtered_lines = original_lines;
  filtered_lines.erase(
      std::remove_if(filtered_lines.begin(), filtered_lines.end(),
                     [=](const std::string& str) {
                       return str.length() < length_threshold;
                     }),
      filtered_lines.end());

  // 3. Удаление всех гласных букв из каждой строки
  std::vector<std::string> no_vowels_lines = filtered_lines;
  for (auto& line : no_vowels_lines) {
    line.erase(std::remove_if(line.begin(), line.end(), isVowel), line.end());
  }

  // 4. Поиск строки с заданным словом
  std::string found_line = "Word not found";
  std::string target_word = search_word;
  auto search_iterator =
      std::find_if(no_vowels_lines.begin(), no_vowels_lines.end(),
                   [&target_word](const std::string& str) {
                     return str.find(target_word) != std::string::npos;
                   });

  if (search_iterator != no_vowels_lines.end()) {
    found_line = *search_iterator;
  }

  // 5. Подсчёт общего количества символов во всех строках (без учёта '_')
  size_t total_chars = std::accumulate(
      no_vowels_lines.begin(), no_vowels_lines.end(), size_t{0},
      [](size_t sum, const std::string& str) {
        size_t valid_chars = std::count_if(str.begin(), str.end(),
                                           [](char ch) { return ch != '_'; });
        return sum + valid_chars;
      });

  // 6. Создание нового вектора целых чисел, содержащего длины всех строк
  std::vector<int> line_lengths;
  line_lengths.reserve(no_vowels_lines.size());
  std::transform(no_vowels_lines.begin(), no_vowels_lines.end(),
                 std::back_inserter(line_lengths), [](const std::string& str) {
                   return static_cast<int>(str.length());
                 });

  // Запись в output.txt

  output_file << "=== Исходный вектор строк ===\n";
  for (const auto& line : original_lines) {
    output_file << line << "\n";
  }

  output_file << "\n=== Вектор строк после удаления коротких строк ===\n";
  for (const auto& line : filtered_lines) {
    output_file << line << "\n";
  }

  output_file << "\n=== Вектор строк после удаления гласных букв ===\n";
  for (const auto& line : no_vowels_lines) {
    output_file << line << "\n";
  }

  output_file << "\n=== Результат поиска заданного слова ===\n";
  output_file << found_line << "\n";

  output_file << "\n=== Общее количество символов без '_' ===\n";
  output_file << total_chars << "\n";

  output_file << "\n=== Вектор длин строк ===\n";
  for (int length : line_lengths) {
    output_file << length << " ";
  }
  output_file << "\n";
}
