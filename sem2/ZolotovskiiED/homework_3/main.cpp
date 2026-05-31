#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main() {
  std::ifstream file_input("input.txt");
  std::ofstream file_output("output.txt");

  std::vector<std::string> start_lines;
  std::string line;

  std::size_t max_len_line = 0;
  std::string search_word;

  std::cin >> max_len_line;
  std::cin >> search_word;

  while (std::getline(file_input, line)) {
    start_lines.push_back(line);
  }

  file_output << "Исходный вектор:\n";

  std::for_each(start_lines.begin(), start_lines.end(),
                [&file_output](const std::string& current_line) {
                  file_output << current_line << "\n";
                });

  std::vector<std::string> short_lines = start_lines;

  short_lines.erase(
      std::remove_if(short_lines.begin(), short_lines.end(),
                     [max_len_line](const std::string& current_line) {
                       return current_line.length() < max_len_line;
                     }),
      short_lines.end());

  file_output << "\nВектор после удаления коротких строк:\n";

  std::for_each(short_lines.begin(), short_lines.end(),
                [&file_output](const std::string& current_line) {
                  file_output << current_line << "\n";
                });

  std::vector<std::string> space_lines = short_lines;

  std::for_each(space_lines.begin(), space_lines.end(), [](std::string& current_line) {
    std::replace(current_line.begin(), current_line.end(), ' ', '_');
  });

  file_output << "\nВектор после замены пробелов на '_':\n";

  std::for_each(space_lines.begin(), space_lines.end(),
                [&file_output](const std::string& current_line) {
                  file_output << current_line << "\n";
                });

  std::vector<std::string> found_lines;

  std::copy_if(space_lines.begin(), space_lines.end(), std::back_inserter(found_lines),
               [&search_word](const std::string& current_line) {
                 return current_line.find(search_word) != std::string::npos;
               });

  file_output << "\nРезультат поиска заданного слова:\n";

  if (!found_lines.empty()) {
    std::for_each(found_lines.begin(), found_lines.end(),
                  [&file_output](const std::string& current_line) {
                    file_output << current_line << "\n";
                  });
  } else {
    file_output << "Строки с заданным словом не найдены\n";
  }

  std::vector<std::string> count_lines = space_lines;

  std::for_each(count_lines.begin(), count_lines.end(), [](std::string& current_line) {
    current_line.erase(std::remove(current_line.begin(), current_line.end(), '_'),
                       current_line.end());
  });

  int count_symbols = 0;

  std::for_each(count_lines.begin(), count_lines.end(),
                [&count_symbols](const std::string& current_line) {
                  count_symbols += current_line.length();
                });

  file_output << "\nОбщее количество символов без '_':\n";
  file_output << count_symbols << "\n";

  std::vector<int> len_lines;

  std::transform(space_lines.begin(), space_lines.end(), std::back_inserter(len_lines),
                 [](const std::string& current_line) {
                   return current_line.length();
                 });

  file_output << "\nВектор длин строк:\n";

  std::for_each(len_lines.begin(), len_lines.end(), [&file_output](int current_len) {
    file_output << current_len << " ";
  });

  file_input.close();
  file_output.close();

  return 0;
}
