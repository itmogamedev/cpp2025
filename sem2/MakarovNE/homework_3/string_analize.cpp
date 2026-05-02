#include "string_analize.h"

#include <algorithm>
#include <fstream>
#include <iostream>

void StringAnalize::processFiles(const std::string& input_filename,
                                 const std::string& output_filename,
                                 int threshold,
                                 const std::string& search_word) {
  std::ifstream in(input_filename);
  std::ofstream out(output_filename);
  if (!in.is_open() || !out.is_open()) {
    std::cerr << "Не открылись...\n";
    return;
  }

  // Чтение строк из файла
  std::string line;
  while (std::getline(in, line)) {
    string_data.push_back(line);
  }

  out << "Исходный вектор строк:\n";
  for (const auto& s : string_data) out << s << "\n";

  std::string found_word_line = "Слово не найдено";
  auto containsWord = [&search_word](const std::string& s) {
    return s.find(search_word) != std::string::npos;
  };
  auto it = std::find_if(string_data.begin(), string_data.end(), containsWord);
  if (it != string_data.end()) {
    found_word_line = *it;
  }

  // Удаление строк меньше заданного порога
  string_data.erase(std::remove_if(string_data.begin(), string_data.end(),
                                   [threshold](const std::string& s) {
                                     return s.length() <
                                            static_cast<size_t>(threshold);
                                   }),
                    string_data.end());

  out << "\nВектор строк после удаления коротких строк:\n";
  for (const auto& s : string_data) out << s << "\n";

  // Удаление глассных
  bool remove_vowels = true;
  auto removeVowels = [remove_vowels](std::string& s) {
    s.erase(std::remove_if(s.begin(), s.end(),
                           [remove_vowels](char c) {
                             if (!remove_vowels) return false;
                             char lc =
                                 std::tolower(static_cast<unsigned char>(c));
                             return (lc == 'a' || lc == 'e' || lc == 'i' ||
                                     lc == 'o' || lc == 'u' || lc == 'y');
                           }),
            s.end());
  };
  std::for_each(string_data.begin(), string_data.end(), removeVowels);

  out << "\nВектор строк после удаления гласных:\n";
  for (const auto& s : string_data) out << s << "\n";

  // Поиск заданного слова

  out << "\nРезультат поиска заданного слова:\n";
  out << found_word_line << "\n";

  // Подсчет количества символов без пробелов
  int char_count = 0;
  auto countChars = [&char_count](const std::string& s) {
    char_count +=
        std::count_if(s.begin(), s.end(), [](char c) { return c != ' '; });
  };
  std::for_each(string_data.begin(), string_data.end(), countChars);

  out << "\nОбщее количество символов без пробелов:\n";
  out << char_count << "\n";

  std::vector<int> string_lengths;
  string_lengths.reserve(string_data.size());
  std::transform(string_data.begin(), string_data.end(),
                 std::back_inserter(string_lengths),
                 [](const std::string& s) { return s.length(); });

  out << "\nДлины строк:\n";
  for (int len : string_lengths) {
    out << len << " ";
  }
  out << "\n";
}
