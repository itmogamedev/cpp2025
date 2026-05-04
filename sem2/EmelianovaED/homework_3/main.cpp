#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> lines_orig;
std::vector<std::string> lines_rem;
std::vector<std::string> lines_rep;
std::vector<int> len_lines;
std::string result_serch;
int char_count = 0;
// Прочтение файла
std::vector<std::string> readFile(const std::string& filename) {
  std::vector<std::string> lines_in;
  std::ifstream file_txt(filename.c_str());
  std::string line_in;

  if (!file_txt.is_open()) {
    std::cout << "Error open input.txt" << filename << std::endl;
    return lines_in;
  }
  while (std::getline(file_txt, line_in)) {
    lines_in.push_back(line_in);
  }
  file_txt.close();
  return lines_in;
}
// Удаление короткой строки
void removeShortLines(std::vector<std::string>& lines, int threshold) {
  auto is_short = [threshold](const std::string& str) {
    return str.length() < static_cast<size_t>(threshold);
  };
  lines.erase(std::remove_if(lines.begin(), lines.end(), is_short),
              lines.end());
}
// Замена символов пробела на _
void replaceSpaces(std::vector<std::string>& lines) {
  auto replace_char = [](char ch) {
    if (ch == ' ') {
      return '_';
    }
    return ch;
  };

  auto all_strings = [&replace_char](std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), replace_char);
  };

  std::for_each(lines.begin(), lines.end(), all_strings);
}
// Поиск строки по слову
std::string findWord(const std::vector<std::string>& lines,
                     const std::string& word) {
  auto contains_word = [&word](const std::string& str) {
    return str.find(word) != std::string::npos;
  };
  auto id_ln = std::find_if(lines.begin(), lines.end(), contains_word);

  if (id_ln != lines.end()) {
    return *id_ln;
  }
  return "Не найдено";
}

// Функция для подсчета символов без _
int countCharsWithoutUnderscore(const std::vector<std::string>& lines) {
  int count_ch = 0;
  auto count_in_string = [](const std::string& str) {
    int c = 0;
    for (size_t j = 0; j < str.length(); j++) {
      if (str[j] != '_') {
        c++;
      }
    }
    return c;
  };
  auto accumulate_ch = [&count_ch, &count_in_string](const std::string& str) {
    count_ch += count_in_string(str);
  };

  std::for_each(lines.begin(), lines.end(), accumulate_ch);

  return count_ch;
}

// Функция для получения длин строк
std::vector<int> getLengths(const std::vector<std::string>& lines) {
  std::vector<int> lens_ln;
  lens_ln.resize(lines.size());
  auto getLength = [](const std::string& str) {
    return static_cast<int>(str.length());
  };
  std::transform(lines.begin(), lines.end(), lens_ln.begin(), getLength);

  return lens_ln;
}

// Функция для записи результатов в output.txt
void writeFullResults() {
  std::ofstream file_out("output.txt");

  if (!file_out.is_open()) {
    std::cout << "Ошибка: не могу создать output.txt" << std::endl;
    return;
  }

  file_out << "Lines in input.txt" << std::endl;
  for (size_t i = 0; i < lines_orig.size(); i++) {
    file_out << lines_orig[i] << std::endl;
  }

  file_out << std::endl << "Lines after delete short strings" << std::endl;
  for (size_t i = 0; i < lines_rem.size(); i++) {
    file_out << lines_rem[i] << std::endl;
  }

  file_out << std::endl << "Lines after replace" << std::endl;
  for (size_t i = 0; i < lines_rep.size(); i++) {
    file_out << lines_rep[i] << std::endl;
  }

  file_out << std::endl << "Result serch: ";
  file_out << result_serch << std::endl;

  file_out << std::endl << "Count char: ";
  file_out << char_count << std::endl;

  file_out << std::endl << "Lens lines" << std::endl;
  for (size_t i = 0; i < len_lines.size(); i++) {
    file_out << "Line " << i + 1 << ": " << len_lines[i] << " chars"
             << std::endl;
  }

  file_out.close();
}

// Главная функция обработки
void processLines(std::vector<std::string>& lines) {
  lines_orig = lines;

  int threshold_ln;
  std::cout << "Enter a threshold for the length of the string: ";
  std::cin >> threshold_ln;

  removeShortLines(lines, threshold_ln);
  lines_rem = lines;

  replaceSpaces(lines);
  lines_rep = lines;

  std::string word_us;
  std::cout << "Enter the search word: ";
  std::cin >> word_us;
  result_serch = findWord(lines, word_us);

  char_count = countCharsWithoutUnderscore(lines);

  len_lines = getLengths(lines);

  writeFullResults();
}
int main() {
  std::vector<std::string> lines = readFile("input.txt");
  processLines(lines);
}
