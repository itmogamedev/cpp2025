#include "text_processor.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace {

void printStrings(std::ostream& out, const std::vector<std::string>& vec,
                  const std::string& header) {
  out << header << ":\n";
  for (size_t i = 0; i < vec.size(); ++i) {
    out << i + 1 << ": " << vec[i] << '\n';
  }
  out << '\n';
}

std::string removeVowels(const std::string& s) {
  std::string result = s;
  result.erase(std::remove_if(result.begin(), result.end(),
                              [](char c) {
                                const std::string vowels = "aeiouyAEIOUY";
                                return vowels.find(c) != std::string::npos;
                              }),
               result.end());
  return result;
}

void getUserInput(size_t& threshold, std::string& search_word) {
  std::cout << "Введите порог длины строки: ";
  std::cin >> threshold;
  std::cin.ignore();
  std::cout << "Введите слово для поиска: ";
  std::getline(std::cin, search_word);
}

}  // namespace

void run() {
  std::ifstream fin("input.txt");
  if (!fin) {
    std::cerr << "Не удалось открыть input.txt\n";
    return;
  }
  std::vector<std::string> original;
  std::string line;
  while (std::getline(fin, line)) {
    original.push_back(line);
  }
  fin.close();

  size_t threshold = 0;
  std::string search_word;
  getUserInput(threshold, search_word);

  std::vector<std::string> filtered = original;
  auto new_end = std::remove_if(
      filtered.begin(), filtered.end(),
      [threshold](const std::string& s) { return s.length() < threshold; });
  filtered.erase(new_end, filtered.end());

  std::vector<std::string> no_vowels;
  no_vowels.reserve(filtered.size());
  std::transform(filtered.begin(), filtered.end(),
                 std::back_inserter(no_vowels), removeVowels);

  auto it = std::find_if(no_vowels.begin(), no_vowels.end(),
                         [&search_word](const std::string& s) {
                           return s.find(search_word) != std::string::npos;
                         });
  std::string search_result;
  if (it != no_vowels.end()) {
    search_result = "Слово \"" + search_word + "\" найдено в строке: " + *it;
  } else {
    search_result = "Слово \"" + search_word + "\" не найдено.";
  }

  size_t total_chars_no_underscore = std::accumulate(
      no_vowels.begin(), no_vowels.end(), 0ULL,
      [](size_t sum, const std::string& s) {
        return sum + std::count_if(s.begin(), s.end(),
                                   [](char c) { return c != '_'; });
      });

  std::vector<int> lengths;
  lengths.reserve(no_vowels.size());
  std::transform(
      no_vowels.begin(), no_vowels.end(), std::back_inserter(lengths),
      [](const std::string& s) { return static_cast<int>(s.length()); });

  std::ofstream fout("output.txt");
  if (!fout) {
    std::cerr << "Не удалось создать output.txt\n";
    return;
  }

  printStrings(fout, original, "Исходный вектор строк");
  printStrings(fout, filtered,
               "Вектор строк после удаления коротких строк (длина < " +
                   std::to_string(threshold) + ")");
  printStrings(fout, no_vowels,
               "Вектор строк после удаления гласных букв (вариант 2)");
  fout << "Результат поиска заданного слова:\n" << search_result << "\n\n";
  fout << "Общее количество символов без '_': " << total_chars_no_underscore
       << "\n\n";
  fout << "Вектор длин строк:\n";
  for (size_t i = 0; i < lengths.size(); ++i) {
    fout << lengths[i] << (i + 1 < lengths.size() ? ", " : "");
  }
  fout << '\n';

  std::cout << "Обработка завершена. Результат сохранён в output.txt\n";
}
