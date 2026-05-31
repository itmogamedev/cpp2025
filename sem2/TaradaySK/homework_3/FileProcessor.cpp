#include "FileProcessor.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void processFiles() {
  std::vector<std::string> lines;
  std::string text;
  std::string line = "------------------------------------------------------";

  std::ifstream input("input.txt");
  if (input.is_open()) {
    while (std::getline(input, text)) {
      lines.push_back(text);
    }
  }
  input.close();

  std::ofstream output("output.txt");
  if (output.is_open()) {
    output << line << "\n(-_-) Исходный вектор(-_-)\n";
    for (const auto& s : lines) output << s << "\n";

    int threshold;
    std::cout << "Введите порог длины: ";
    std::cin >> threshold;
    lines.erase(std::remove_if(lines.begin(), lines.end(),
                               [threshold](const std::string& s) {
                                 return s.length() < (size_t)threshold;
                               }),
                lines.end());
    output << line << "\n(-_-) После удаления строк < " << threshold
           << " (-_-)\n";
    for (const auto& s : lines) output << s << "\n";

    for (auto& s : lines) {
      for (char& c : s)
        if (c == ' ') c = '_';
    }
    output << line << "\n(-_-) После замены пробелов на _ (-_-)\n";
    for (const auto& s : lines) output << s << "\n";

    std::string searchWord;
    std::cout << "Введите слово для поиска: ";
    std::cin >> searchWord;
    auto it = std::find_if(lines.begin(), lines.end(),
                           [&searchWord](const std::string& s) {
                             return s.find(searchWord) != std::string::npos;
                           });
    output << line << "\n(-_-) Результат поиска по " << searchWord
           << " (-_-)\n";
    if (it != lines.end())
      output << *it << "\n";
    else
      output << "Слово не найдено\n";

    long long total = 0;
    for (const auto& s : lines) {
      for (char c : s)
        if (c != '_') total++;
    }
    output << line << "\n(-_-) Символов без _ (-_-)\n" << total << "\n";

    std::vector<int> lengths;
    for (const auto& s : lines) lengths.push_back((int)s.length());
    output << line << "\n(-_-) Длины строк (-_-)\n";
    for (int l : lengths) output << l << " ";
  }
  output.close();
}
