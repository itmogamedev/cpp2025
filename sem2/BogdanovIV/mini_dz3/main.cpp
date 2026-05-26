
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string line;
  std::ifstream file("input.txt");
  std::ofstream out("output.txt");
  std::vector<std::string> lines;

  auto WriteLinesInFile = [&lines, &out](std::string title) {
    out << "\n======" + title + "======\n";
    for (std::string& str : lines) {
      out << str << '\n';
    }
  };

  if (file.is_open()) {
    while (std::getline(file, line)) {
      lines.push_back(line);
    }
    file.close();
  } else {
    std::cerr << "cant open file" << std::endl;
  }

  WriteLinesInFile("Start");
  int min_line_length;

  std::cout << "Input min line lenght: ";
  std::cin >> min_line_length;

  lines.erase(std::remove_if(lines.begin(), lines.end(),
                             [min_line_length](const std::string& line) {
                               return line.size() < min_line_length;
                             }),
              lines.end());

  WriteLinesInFile("After delete small strings");
  std::for_each(lines.begin(), lines.end(), [](std::string& str) {
    std::replace(str.begin(), str.end(), ' ', '_');
  });

  WriteLinesInFile("After replace");

  std::string find_word;
  std::cout << "Write find word: ";
  std::cin >> find_word;

  auto find = std::find_if(lines.begin(), lines.end(),
                           [&find_word](const std::string& str) {
                             return str.find(find_word) != std::string::npos;
                           });

  if (find != lines.end()) {
    out << "\n=====Find=====\n";
    out << *find << '\n';
  }

  auto sym_count = [&lines]() {
    int count = 0;
    for (std::string& str : lines)
      for (char ch : str) {
        if (ch != '_') ++count;
      }

    return count;
  };

  out << "\n=====Sym count=====\ncount: " << std::to_string(sym_count())
      << '\n';

  std::vector<int> line_sym_count;

  auto set_line_sym_count = [&lines, &line_sym_count, &out]() {
    out << "\n=====Line Sym Count=====\n";
    for (std::string& str : lines) {
      line_sym_count.push_back(str.size());
      out << str.size() << '\n';
    }
  };
  set_line_sym_count();

  return 0;
}
