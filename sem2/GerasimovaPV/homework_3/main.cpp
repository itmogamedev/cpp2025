#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// проверка гласной буквы
bool isVowel(char c) {
  c = std::tolower(static_cast<unsigned char>(c));
  return (c == 'a' || c == 'e' || c == 'i' ||
          c == 'o' || c == 'u' || c == 'y');
}

int main() {
  std::ifstream input_file("input.txt");
  std::ofstream output_file("output.txt");

  if (!input_file) {
    std::cout << "Cannot open input.txt\n";
    return 1;
  }

  std::vector<std::string> lines;
  std::string line;

  // читаем файл
  while (std::getline(input_file, line)) {
    lines.push_back(line);
  }

  std::vector<std::string> original_lines = lines;

  // удаление строк короче порога
  int min_length;
  std::cout << "Enter minimum length: ";
  std::cin >> min_length;

  lines.erase(
      std::remove_if(lines.begin(), lines.end(),
                     [min_length](const std::string& s) {
                       return s.size() < min_length;
                     }),
      lines.end());

  std::vector<std::string> filtered_lines = lines;

  // удаление гласных
  std::vector<std::string> no_vowel_lines = filtered_lines;

  for (auto& s : no_vowel_lines) {
    s.erase(std::remove_if(s.begin(), s.end(), isVowel), s.end());
  }

  // поиск строки по слову
  std::string word;
  std::cout << "Enter word to search: ";
  std::cin >> word;

  std::string found_line;
  bool found = false;

  auto search_lambda = [&word, &found, &found_line](const std::string& s) {
    if (s.find(word) != std::string::npos) {
      found = true;
      found_line = s;
    }
  };

  for (const auto& s : filtered_lines) {
    search_lambda(s);
  }

  // подсчёт символов без _
  long long total_chars = 0;

  for (const auto& s : no_vowel_lines) {
    for (char c : s) {
      if (c != '_') {
        total_chars++;
      }
    }
  }

  // вектор длин строк
  std::vector<int> lengths;
  for (const auto& s : no_vowel_lines) {
    lengths.push_back(static_cast<int>(s.size()));
  }

  // запись в файл
  output_file << " ORIGINAL STRINGS \n";
  for (const auto& s : original_lines) {
    output_file << s << "\n";
  }

  output_file << "\n AFTER REMOVING SHORT STRINGS \n";
  for (const auto& s : filtered_lines) {
    output_file << s << "\n";
  }

  output_file << "\n AFTER REMOVING VOWELS \n";
  for (const auto& s : no_vowel_lines) {
    output_file << s << "\n";
  }

  output_file << "\n SEARCH RESULT \n";
  if (found) {
    output_file << found_line << "\n";
  } else {
    output_file << "Not found\n";
  }

  output_file << "\n TOTAL CHARACTERS no '_' \n";
  output_file << total_chars << "\n";

  output_file << "\n LENGTHS \n";
  for (int len : lengths) {
    output_file << len << " ";
  }
  output_file << "\n";

  return 0;
}