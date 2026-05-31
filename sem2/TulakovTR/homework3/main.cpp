#include <windows.h>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  SetConsoleOutputCP(1251);
  SetConsoleCP(1251);

  std::ifstream inputFile("input.txt");
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(inputFile, line)) {
    lines.push_back(line);
  }
  inputFile.close();

  std::vector<std::string> originalLines = lines;

  size_t threshold;
  std::cout << "Введите минимальную длину строки: ";
  std::cin >> threshold;
  std::cin.ignore();

  // Лямбда: удаление строк короче порога (захват по значению)
  auto removeShortLines = [threshold](std::vector<std::string>& vec) {
    vec.erase(std::remove_if(vec.begin(), vec.end(),
                             [threshold](const std::string& str) {
                               return str.length() < threshold;
                             }),
              vec.end());
  };

  std::vector<std::string> filteredLines = lines;
  removeShortLines(filteredLines);

  // Лямбда: удаление гласных (Вариант 2)
  auto removeVowels = [](std::string& str) {
    str.erase(
        std::remove_if(str.begin(), str.end(),
                       [](char c) {
                         char lower = tolower(static_cast<unsigned char>(c));
                         return lower == 'a' || lower == 'e' || lower == 'i' ||
                                lower == 'o' || lower == 'u' || lower == 'y';
                       }),
        str.end());
  };

  std::vector<std::string> noVowelsLines = filteredLines;
  for (auto& s : noVowelsLines) {
    removeVowels(s);
  }

  std::string searchWord;
  std::cout << "Введите слово для поиска: ";
  std::getline(std::cin, searchWord);

  // Лямбда: поиск строки со словом (захват по ссылке)
  std::string foundLine = "";
  auto searchForWord = [&searchWord,
                        &foundLine](const std::vector<std::string>& vec) {
    auto it = std::find_if(vec.begin(), vec.end(),
                           [&searchWord](const std::string& str) {
                             return str.find(searchWord) != std::string::npos;
                           });
    if (it != vec.end()) {
      foundLine = *it;
    }
  };
  searchForWord(noVowelsLines);

  // Лямбда: подсчёт символов без '_'
  auto countTotalChars = [](const std::vector<std::string>& vec) -> size_t {
    size_t total = 0;
    for (const auto& str : vec) {
      for (char c : str) {
        if (c != '_') total++;
      }
    }
    return total;
  };
  size_t totalChars = countTotalChars(noVowelsLines);

  // Лямбда: вектор длин строк
  auto createLengthVector =
      [](const std::vector<std::string>& vec) -> std::vector<int> {
    std::vector<int> lengths;
    for (const auto& str : vec) {
      lengths.push_back(static_cast<int>(str.length()));
    }
    return lengths;
  };
  std::vector<int> stringLengths = createLengthVector(noVowelsLines);

  std::ofstream outputFile("output.txt");

  outputFile << "=== РЕЗУЛЬТАТЫ ===\n\n";

  outputFile << "1. Исходный вектор строк:\n";
  for (size_t i = 0; i < originalLines.size(); i++) {
    outputFile << "  [" << i << "] \"" << originalLines[i] << "\"\n";
  }
  outputFile << "\n";

  outputFile << "Порог длины: " << threshold << "\n";
  outputFile << "2. После удаления коротких строк:\n";
  for (size_t i = 0; i < filteredLines.size(); i++) {
    outputFile << "  [" << i << "] \"" << filteredLines[i] << "\"\n";
  }
  outputFile << "\n";

  outputFile << "3. После удаления гласных (Вариант 2):\n";
  for (size_t i = 0; i < noVowelsLines.size(); i++) {
    outputFile << "  [" << i << "] \"" << noVowelsLines[i] << "\"\n";
  }
  outputFile << "\n";

  outputFile << "4. Поиск слова \"" << searchWord << "\":\n";
  if (!foundLine.empty()) {
    outputFile << "   Найдено: \"" << foundLine << "\"\n";
  } else {
    outputFile << "   Не найдено\n";
  }
  outputFile << "\n";

  outputFile << "5. Общее количество символов (без '_'): " << totalChars
             << "\n\n";

  outputFile << "6. Вектор длин строк: [";
  for (size_t i = 0; i < stringLengths.size(); i++) {
    outputFile << stringLengths[i];
    if (i < stringLengths.size() - 1) outputFile << ", ";
  }
  outputFile << "]\n";

  outputFile.close();

  std::cout << "Готово! Результаты в output.txt\n";
  system("pause");
  return 0;
}