#include "text_processor.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <numeric>

TextProcessor::TextProcessor(const std::string& input_file_name,
                             const std::string& output_file_name)
    : input_file_name(input_file_name),
      output_file_name(output_file_name) {}

void TextProcessor::run() {
  int min_length = 0;
  std::string search_word;

  std::cout << "Введите минимальную длину строки: ";
  std::cin >> min_length;

  std::cout << "Введите слово для поиска: ";
  std::cin >> search_word;

  std::vector<std::string> original_lines = readLines();
  std::vector<std::string> filtered_lines =
      removeShortLines(original_lines, min_length);
  std::vector<std::string> changed_lines = removeVowels(filtered_lines);

  std::string found_line = findLineWithWord(changed_lines, search_word);
  int total_symbols = countSymbolsWithoutUnderscores(changed_lines);
  std::vector<int> lengths = getLineLengths(changed_lines);

  writeResult(original_lines, filtered_lines, changed_lines, found_line,
              total_symbols, lengths);
}

std::vector<std::string> TextProcessor::readLines() const {
  std::ifstream input_file(input_file_name);
  std::vector<std::string> lines;
  std::string line;

  if (!input_file.is_open()) {
    std::cout << "Не удалось открыть файл " << input_file_name << '\n';
    return lines;
  }

  while (std::getline(input_file, line)) {
    lines.push_back(line);
  }

  return lines;
}

std::vector<std::string> TextProcessor::removeShortLines(
    const std::vector<std::string>& lines, int min_length) const {
  std::vector<std::string> filtered_lines = lines;

  filtered_lines.erase(
      std::remove_if(filtered_lines.begin(), filtered_lines.end(),
                     [min_length](const std::string& line) {
                       return static_cast<int>(line.length()) < min_length;
                     }),
      filtered_lines.end());

  return filtered_lines;
}

std::vector<std::string> TextProcessor::removeVowels(
    const std::vector<std::string>& lines) const {
  std::vector<std::string> changed_lines = lines;

  std::for_each(changed_lines.begin(), changed_lines.end(),
                [this](std::string& line) {
                  line.erase(std::remove_if(line.begin(), line.end(),
                                            [this](char symbol) {
                                              return isVowel(symbol);
                                            }),
                             line.end());
                });

  return changed_lines;
}

std::string TextProcessor::findLineWithWord(
    const std::vector<std::string>& lines,
    const std::string& search_word) const {
  std::string word = search_word;

  auto found_line = std::find_if(
      lines.begin(), lines.end(), [&word](const std::string& line) {
        return line.find(word) != std::string::npos;
      });

  if (found_line == lines.end()) {
    return "";
  }

  return *found_line;
}

int TextProcessor::countSymbolsWithoutUnderscores(
    const std::vector<std::string>& lines) const {
  return std::accumulate(
      lines.begin(), lines.end(), 0, [](int sum, const std::string& line) {
        return sum + static_cast<int>(std::count_if(
                         line.begin(), line.end(),
                         [](char symbol) { return symbol != '_'; }));
      });
}

std::vector<int> TextProcessor::getLineLengths(
    const std::vector<std::string>& lines) const {
  std::vector<int> lengths;

  std::transform(lines.begin(), lines.end(), std::back_inserter(lengths),
                 [](const std::string& line) {
                   return static_cast<int>(line.length());
                 });

  return lengths;
}

bool TextProcessor::isVowel(char symbol) const {
  char lower_symbol =
      static_cast<char>(std::tolower(static_cast<unsigned char>(symbol)));

  return lower_symbol == 'a' || lower_symbol == 'e' || lower_symbol == 'i' ||
         lower_symbol == 'o' || lower_symbol == 'u' || lower_symbol == 'y';
}

void TextProcessor::writeResult(
    const std::vector<std::string>& original_lines,
    const std::vector<std::string>& filtered_lines,
    const std::vector<std::string>& changed_lines,
    const std::string& found_line,
    int total_symbols,
    const std::vector<int>& lengths) const {
  std::ofstream output_file(output_file_name);

  if (!output_file.is_open()) {
    std::cout << "Не удалось открыть файл " << output_file_name << '\n';
    return;
  }

  output_file << "Исходный вектор строк:\n";
  for (const std::string& line : original_lines) {
    output_file << line << '\n';
  }

  output_file << "\nВектор строк после удаления коротких строк:\n";
  for (const std::string& line : filtered_lines) {
    output_file << line << '\n';
  }

  output_file << "\nВектор строк после удаления гласных букв:\n";
  for (const std::string& line : changed_lines) {
    output_file << line << '\n';
  }

  output_file << "\nРезультат поиска заданного слова:\n";
  if (!found_line.empty()) {
    output_file << "Найдена строка: " << found_line << '\n';
  } else {
    output_file << "Строка не найдена\n";
  }

  output_file << "\nОбщее количество символов без \"_\":\n";
  output_file << total_symbols << '\n';

  output_file << "\nВектор длин строк:\n";
  for (int length : lengths) {
    output_file << length << ' ';
  }

  output_file << '\n';
}