#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void solve() {
  std::ifstream file_input("input.txt");
  std::string line;
  std::vector<std::string> lines;

  while (std::getline(file_input, line)) {
    lines.push_back(line);
  }
  file_input.close();

  std::vector<std::string> original_lines = lines;

  int length;
  std::cin >> length;
  std::string word;
  std::cin >> word;

  auto is_shorter_length = [length](const std::string& str) {
    return str.length() < length;
  };

  lines.erase(std::remove_if(lines.begin(), lines.end(), is_shorter_length),
              lines.end());
  std::vector<std::string> after_removal = lines;

  auto is_vowel = [](char ch) {
    char lower_letter = std::tolower(ch);
    return lower_letter == 'a' || lower_letter == 'e' || lower_letter == 'i' ||
           lower_letter == 'o' || lower_letter == 'u' || lower_letter == 'y';
  };

  std::vector<std::string> without_vowels = lines;

  for (auto& str : without_vowels) {
    str.erase(std::remove_if(str.begin(), str.end(), is_vowel), str.end());
  }

  auto contains_word = [&](const std::string& str) {
    return str.find(word) != std::string::npos;
  };

  auto it =
      std::find_if(original_lines.begin(), original_lines.end(), contains_word);
  std::string search_result;
  if (it != original_lines.end()) {
    search_result = "Слово " + word + " найдено в строке: " + *it;
  } else {
    search_result = "Слово " + word + " не найдено ни в одной строке";
  }

  int letters_count = 0;
  for (const auto& str : without_vowels) {
    letters_count += str.length();
  }

  std::vector<int> lengths;
  for (const auto& str : after_removal) {
    lengths.push_back(str.length());
  }

  std::ofstream file_output("output.txt");
  for (std::string& row : original_lines) file_output << row << std::endl;
  file_output << "" << std::endl;
  for (std::string& row : after_removal) file_output << row << std::endl;
  file_output << "" << std::endl;
  for (std::string& row : without_vowels) file_output << row << std::endl;
  file_output << "" << std::endl;
  file_output << search_result << std::endl;
  file_output << "" << std::endl;
  file_output << letters_count << std::endl;
  file_output << "" << std::endl;
  for (int& len : lengths) file_output << std::to_string(len) + "\n";
}

int main() {
  solve();

  return 0;
}
