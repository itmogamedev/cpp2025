#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool isVowel(char c) {
  char lower = std::tolower(static_cast<unsigned char>(c));
  return (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' ||
          lower == 'u' || lower == 'y');
}

int main() {
  std::ifstream inFile("input.txt");
  if (!inFile.is_open()) {
    std::cerr << "Error: cannot open input.txt" << std::endl;
    return 1;
  }

  std::vector<std::string> lines;
  std::string line;

  while (std::getline(inFile, line)) {
    lines.push_back(line);
  }
  inFile.close();

  int porog;
  std::cout << "Enter length porog: ";
  std::cin >> porog;

  // удаление строк короче порога (захват по значению)
  auto removeShort = [porog](const std::string& s) {
    return static_cast<int>(s.length()) < porog;
  };
  std::vector<std::string> afterRemove = lines;
  afterRemove.erase(
      std::remove_if(afterRemove.begin(), afterRemove.end(), removeShort),
      afterRemove.end());

  // удаление гласных из каждой строки
  std::vector<std::string> afterProcess = afterRemove;
  for (auto& str : afterProcess) {
    str.erase(std::remove_if(str.begin(), str.end(),
                             [](char c) { return isVowel(c); }),
              str.end());
  }

  // поиск строки с заданным словом (захват по ссылке)
  std::string searchWord;
  std::cout << "Enter word to search: ";
  std::cin >> searchWord;
  auto searchLambda = [&searchWord](const std::string& s) {
    return s.find(searchWord) != std::string::npos;
  };
  auto it =
      std::find_if(afterProcess.begin(), afterProcess.end(), searchLambda);
  std::string searchResult = (it != afterProcess.end()) ? *it : "Not found";

  // подсчёт общего количества символов
  int totalChars = 0;
  for (const auto& str : afterProcess) {
    for (char c : str) {
      if (c != '_') {
        ++totalChars;
      }
    }
  }

  // создание вектора длин строк
  std::vector<int> lengths;
  for (const auto& str : afterProcess) {
    lengths.push_back(static_cast<int>(str.length()));
  }

  // вывод в output.txt
  std::ofstream outFile("output.txt");
  if (!outFile.is_open()) {
    std::cerr << "Error: cannot create output.txt" << std::endl;
    return 1;
  }

  outFile << "*+- Original lines -+*\n";
  for (const auto& l : lines) {
    outFile << l << "\n";
  }

  outFile << "\n*+- After removing short lines (porog = " << porog << ") -+*\n";
  for (const auto& l : afterRemove) {
    outFile << l << "\n";
  }

  outFile << "\n*+- After removing vowels -+*\n";
  for (const auto& l : afterProcess) {
    outFile << l << "\n";
  }

  outFile << "\n*+- Search result for \"" << searchWord << "\" -+*\n";
  outFile << searchResult << "\n";

  outFile << "\n*+- Total characters (excluding '_') -+*\n";
  outFile << totalChars << "\n";

  outFile << "\n*+- Lengths of strings -+*\n";
  for (int len : lengths) {
    outFile << len << " ";
  }
  outFile << "\n";

  outFile.close();

  std::cout << "\nProcessing completed! Check output.txt" << std::endl;

  return 0;
}
