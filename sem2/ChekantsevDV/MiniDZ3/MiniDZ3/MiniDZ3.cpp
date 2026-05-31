#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
  setlocale(LC_ALL, "rus");
  std::ifstream input_file("input.txt");
  std::vector<std::string> text_lines;
  std::string current_line;
  while (std::getline(input_file, current_line)) {
    text_lines.push_back(current_line);
  }
  input_file.close();
  const auto original_text_lines = text_lines;

  std::cout << "Введите порог длины строки: ";
  size_t min_line_length;
  std::cin >> min_line_length;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << "Введите искомое слово: ";
  std::string target_word;
  std::getline(std::cin, target_word);

  text_lines.erase(std::remove_if(text_lines.begin(), text_lines.end(),
                                  [min_line_length](const std::string& s) {
                                    return s.length() < min_line_length;
                                  }),
                   text_lines.end());
  const auto filtered_lines = text_lines;

  std::for_each(text_lines.begin(), text_lines.end(), [](std::string& s) {
    s.erase(std::remove_if(s.begin(), s.end(),
                           [](char c) {
                             c = std::tolower(static_cast<unsigned char>(c));
                             return c == 'a' || c == 'e' || c == 'i' ||
                                    c == 'o' || c == 'u' || c == 'y';
                           }),
            s.end());
  });
  const auto vowel_less_lines = text_lines;

  std::string found_sentence;
  auto found_iter =
      std::find_if(vowel_less_lines.begin(), vowel_less_lines.end(),
                   [&target_word](const std::string& s) {
                     return s.find(target_word) != std::string::npos;
                   });
  found_sentence = (found_iter != vowel_less_lines.end())
                       ? *found_iter
                       : "Слово \"" + target_word + "\" не найдено.";

  size_t total_chars_without_vowels = std::accumulate(
      vowel_less_lines.begin(), vowel_less_lines.end(), 0UL,
      [](size_t sum, const std::string& s) { return sum + s.size(); });

  std::vector<size_t> line_lengths;
  line_lengths.reserve(vowel_less_lines.size());
  std::transform(vowel_less_lines.begin(), vowel_less_lines.end(),
                 std::back_inserter(line_lengths),
                 [](const std::string& s) { return s.size(); });

  std::ofstream output_file("output.txt");
  auto write_lines_title = [&output_file](const std::string& title,
                                          const auto& vec) {
    output_file << title << ":\n";
    for (const auto& item : vec) {
      output_file << item << '\n';
    }
    output_file << '\n';
  };

  write_lines_title("Исходный вектор строк", original_text_lines);
  write_lines_title("Вектор строк после удаления коротких строк",
                    filtered_lines);
  write_lines_title("Вектор строк после удаления гласных букв",
                    vowel_less_lines);

  output_file << "Результат поиска заданного слова \"" << target_word << "\":\n"
              << found_sentence << "\n\n";
  output_file << "Общее количество символов без всех гласных букв: "
              << total_chars_without_vowels << "\n\n";
  output_file << "Вектор длин строк:\n";
  for (size_t len : line_lengths) {
    output_file << len << ' ';
  }
  output_file << '\n';
  output_file.close();
}
